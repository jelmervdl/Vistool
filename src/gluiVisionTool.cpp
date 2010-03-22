#include "gluiVisionTool.h"

using namespace std;

states::DisplayMode      dm = states::Single_Image;
states::DatasetOnDisplay ds = states::Enabled_Datasets;
states::DisplayModifier display_modifier = states::No_Modifier;

ParameterPanel *    parameter_panel;
Dataset *           current_db;
size_t              current_image_page = 0;
vector <Texture *>    textures;
vector <DataPoint*> currently_view_datapoints; 
vector <DataPoint>  train_data, test_data;
vector <int>        test_result;
Classifier *        current_classifier;

// class view selection
int            selected_class;
Evaluation *   current_evaluation;
GLUI_Listbox * selected_class_listbox;
vector<int>    current_classes;

//Global Glui Objects 
GLUI_StaticText * busytxt;
GLUI *            main_gui;
GLUI *            classes;
GLUI *            stats;
int               ims_per_page = 16;

// main window
size_t window_width;
size_t window_height;
int    image_display_window;
  
// Single Image parameters
Texture * current_single_image_texture;
size_t image_width; 
size_t image_height;
DataPoint * singleDp;

void quitf(){
  delete current_db;
  delete current_single_image_texture;
  delete singleDp;
  delete busytxt;
  delete main_gui;
  delete classes;
  delete current_evaluation;
  exit(0);
}

void start(int argc, char **argv){
  glutInit(&argc, argv); // obligatory glut call
  printf("Starting up glut...\n"); 
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  setupWindow();
  glutDisplayFunc(display);
  setupOpenGL();
  display();
  initGlui();
  glutMainLoop();
}

void setupWindow(){
  glutInitWindowPosition( 0, 0 );
  window_height = 800;
  window_width = 800;
  glutInitWindowSize( window_width, window_height );
  image_display_window = glutCreateWindow( "Image Viewer" );
}

void setupOpenGL(){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, window_height, window_width, 0, 0, 1); // we want 2d projection mode!                                                                                       
  glMatrixMode(GL_MODELVIEW); // bring us back to model mode                                                                                          
  glDisable( GL_DEPTH_TEST); //2d, no depth                                                                                                           
  glDisable( GL_LIGHTING ); // 2d, no light  
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}

void askDataset(){
  loadDataset(askFile());
}

void loadDataset(string location){
  if(classes != 0)
    classes->close();
  classes = GLUI_Master.create_glui( "classes", 0, 800, 250 );
  delete current_db;
  current_db = new Dataset(location);
  vector<Category> * cats = current_db->getCategories();
  size_t c = 0;
  //  classes->add_column(true);
  GLUI_Panel * pan = classes->add_panel("categories");
  if(current_db != NULL){
    for(size_t i = 0; i < cats->size(); ++i){
      classes->add_checkbox_to_panel( pan,
				      (const char *)cats->at(i).getName().c_str(),
				      cats->at(i).getEnabled(),
				      1, (GLUI_Update_CB) viewDataset);
      c++;
      if(c%34==0)
	classes->add_column_to_panel(pan, false);
    }
  }
}

void loadPicture(){
  dm = states::Single_Image;
  glutSetWindow(image_display_window);
  delete current_single_image_texture;
  delete singleDp;
  string url  = askFile();
  singleDp = new DataPoint(0, "", url, ""); 
  current_single_image_texture = new Texture(singleDp, image_display_window);
}

void display(void){
  using namespace states;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  switch(dm){
  case Single_Image:
    if(current_single_image_texture!=NULL)
      current_single_image_texture->draw(window_height);
    break;
  case Show_Dataset:
    if(current_db != NULL){
      size_t grid = ceil(sqrt(ims_per_page));
      float scale = 1.0/grid;
      glScalef(scale, scale, 0);
      size_t count  = 0;
      glPushMatrix();
      for(vector<Texture *>::iterator it = textures.begin();
	  it != textures.end();
	  ++it){
	(*it)->draw(window_height);
	glTranslatef(800, 0, 0);
	count++;
	if(count == grid){
	  count = 0;
	  glPopMatrix();
	  glTranslatef(0, 800, 0);
	  glPushMatrix();
	}
      }
      glPopMatrix();
    }
    break;
  default:
    break;
  }
  glutSwapBuffers();
}


void myGlutIdle( void )
{
  if ( glutGetWindow() != image_display_window )
    glutSetWindow(image_display_window);
  glutPostRedisplay();
  main_gui->sync_live();
}

void initGlui(){
  parameter_panel = new ParameterPanel();
  main_gui = GLUI_Master.create_glui( "Control", 0, 800, 0 );
  busytxt = main_gui->add_statictext( "waiting" ); 
  GLUI_Panel * load_panel = main_gui->add_panel("load");
  main_gui->add_button_to_panel(load_panel, "Quit", 0,(GLUI_Update_CB)quitf );
  main_gui->add_button_to_panel(load_panel, "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  main_gui->add_button_to_panel(load_panel, "Load Dataset", 0, (GLUI_Update_CB)askDataset );
  main_gui->add_button_to_panel(load_panel, "Load Caltech", 0, (GLUI_Update_CB)loadCaltech );
  main_gui->add_column(false);
  GLUI_Panel * view_panel = main_gui->add_panel("view");
  main_gui->add_button_to_panel(view_panel, "Refresh", 0, (GLUI_Update_CB)viewDataset );
  main_gui->add_statictext_to_panel(view_panel, "Images Per Page:" ); 
  main_gui->add_spinner_to_panel(view_panel, "", GLUI_SPINNER_INT, &ims_per_page);
  main_gui->add_button_to_panel(view_panel, "Next Page", 0, (GLUI_Update_CB)nextPage );
  GLUI_Listbox * image_mod = main_gui->add_listbox_to_panel(view_panel, "show:", (int*) &display_modifier);
  image_mod->add_item(states::No_Modifier, "image");
  image_mod->add_item(states::Show_Gradient, "gradient");
  image_mod->add_item(states::Show_Sift, "sift");
  GLUI_Listbox * aap = main_gui->add_listbox_to_panel(view_panel, "view:", (int*) &ds, 0, 
					 (GLUI_Update_CB)viewDataset);
  aap->add_item(states::Enabled_Datasets, "Enabled");
  aap->add_item(states::Training_DataPoints, "Training Set");
  aap->add_item(states::Testing_DataPoints, "Test set");
  aap->add_item(states::Correct, "Correct");
  aap->add_item(states::Incorrect, "Incorr.");
  aap->add_item(states::Particular_Category, "Sel. Cat.");
  selected_class_listbox = main_gui->add_listbox_to_panel(view_panel, "part. class:", &selected_class, 0, (GLUI_Update_CB)selectAndShow);
  main_gui->add_column(false);
  GLUI_Panel * ml_panel = main_gui->add_panel("ML");
  main_gui->add_button_to_panel(ml_panel, "Get Descriptors", 0, (GLUI_Update_CB)extractFeatures );
  main_gui->add_button_to_panel(ml_panel, "Evaluate", 0, (GLUI_Update_CB)evaluateClassifier);
  //main_gui->add_button_to_panel(ml_panel, "Train", 0, (GLUI_Update_CB)train);
  //main_gui->add_button_to_panel(ml_panel, "Classify", 0, (GLUI_Update_CB)classify);
  main_gui->set_main_gfx_window(image_display_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void loadCaltech(){
  loadDataset("/Users/mauricemulder/workspace/datasets/caltech101/");
}

void viewDataset(){
  if(current_db != NULL){
    dm = states::Show_Dataset;
    setViewSelection();
    refreshTexture(); 
    display();
  }
  current_image_page = 0;
}

void setViewSelection(){
  currently_view_datapoints.clear();

  using namespace states;
  if(ds == Enabled_Datasets){
      vector<Category*> enabs = current_db->getEnabled();
      for(vector<Category*>::iterator cat = enabs.begin(); cat != enabs.end(); ++cat){
	vector<DataPoint> * dps = (*cat)->getDataPoints();
	for(size_t i = 0; i < dps->size(); ++i)
	  currently_view_datapoints.push_back(&dps->at(i));
      }
  }
  if(ds == Training_DataPoints){
    currently_view_datapoints = VisionCore::ptrDeMorgan<DataPoint>(&train_data);
  }

  if(ds == Testing_DataPoints){
    currently_view_datapoints = VisionCore::ptrDeMorgan<DataPoint>(&test_data);
  }
  if(ds == Particular_Category){
    current_evaluation->print();
    currently_view_datapoints.clear();
    if(current_evaluation != NULL)
      currently_view_datapoints = current_evaluation->getInstancesClassifiedAs(selected_class);
  }
  image_width  = window_width / ims_per_page;
  image_height = window_height / ims_per_page;
  refreshTexture();
}

void refreshTexture(size_t p){
  using namespace gradient;
  for(size_t i = 0; i < textures.size(); ++i)
    delete textures[i];
  textures.clear();
  // display images.
  if(display_modifier == states::No_Modifier)
    for(size_t i = p; i < (size_t) ims_per_page + p && i < (size_t) currently_view_datapoints.size() ; ++i)
      textures.push_back(  new Texture (currently_view_datapoints.at(i), image_display_window));
  // display their gradients
  if(display_modifier == states::Show_Gradient)
    for(size_t i = p; i < (size_t) ims_per_page + p && i < (size_t) currently_view_datapoints.size() ; ++i){
      MyImage im (currently_view_datapoints.at(i)->getImageURL());
      Matrix<float> gray_image = im.getGrayscaleMatrix();
      Matrix<Gradient> image_gradient = imageGradient(gray_image);
      textures.push_back( new Texture(&image_gradient, image_display_window));
    }
  //display sift
  if(display_modifier == states::Show_Sift)
    for(size_t i = p; i < (size_t) ims_per_page + p && 
	  i < (size_t) currently_view_datapoints.size(); ++i){
      MyImage im (currently_view_datapoints.at(i)->getImageURL());
      SiftDescriptor s;
      Image canvas;
      s.extract(&im, true, &canvas);
      textures.push_back(new Texture(&canvas, image_display_window));
    }
  //display histpgra,s
  display();
}

void nextPage(){
  current_image_page += ims_per_page;
  if(current_image_page > currently_view_datapoints.size())
    current_image_page = 0;
  refreshTexture(current_image_page);
  display();
}

void evaluateClassifier(){
  extractFeatures();
  train();
  classify();
}

void train(){
  extractFeatures();
  train_data.clear();
  test_data.clear();
  current_db->randomDataSplit(&train_data, &test_data, 0.5, true);
  delete current_classifier;
  current_classifier = new NNClassifier(1);
  current_classifier->train(&train_data);
  for(vector<int>::iterator cl = current_classes.begin(); 
      cl != current_classes.end(); 
      cl++)
    selected_class_listbox->delete_item(*cl);
  current_classes.clear();
  vector<Category*> enabs = current_db->getEnabled();
  for(size_t i = 0; i <  enabs.size(); ++i){
	selected_class_listbox->add_item(enabs[i]->getLabel(), 
					 enabs[i]->getName().c_str());
	current_classes.push_back(enabs[i]->getLabel());
    }
}

void classify(){
  if(current_classifier == NULL)
    train();
  test_result = current_classifier->classify(&test_data);
  delete current_evaluation;
  current_evaluation = new Evaluation(&test_data, &test_result);
  viewDataset();
  showStatistics();
}

void extractFeatures(){
  busytxt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(current_db);
  busytxt->set_text("done");
}

void selectAndShow(){
  ds = states::Particular_Category;
  viewDataset();
}

void showStatistics(){
  if(stats != NULL)
    stats->close();
  stats = GLUI_Master.create_glui("statistics", 0, 1125, 0);
  {
    stringstream strstr;
    strstr  << "Instances: " << current_evaluation->getInstances() << endl;
    stats->add_statictext(strstr.str().c_str());
  } {
    stringstream strstr;
    strstr  << "Correct: " << current_evaluation->getCorrect() << endl;
    stats->add_statictext(strstr.str().c_str());
  } {
     stringstream strstr;
     strstr  << "Performance: " << current_evaluation->getPrecision() << endl;
     stats->add_statictext(strstr.str().c_str());
  }
   // show confusion info
  map<int,int> cormap = current_evaluation->getCorrectMap();
  map<int, int> totmap = current_evaluation->getTotalMap();
  for(map<int, int>::iterator it = cormap.begin();
      it!= cormap.end(); ++it){
    stringstream strstr;
     strstr  << (*it).first << "." <<  current_db->getCatName((*it).first) 
	     << " " << (*it).second <<  "/" << totmap[(*it).first] << endl;
     stats->add_statictext(strstr.str().c_str());
  }
  
 }
