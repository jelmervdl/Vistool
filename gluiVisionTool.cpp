#include "gluiVisionTool.h"

using namespace std;

states::DisplayMode dm = states::Single_Image;
states::DatasetOnDisplay ds = states::Enabled_Datasets;
Dataset * currentdb;
size_t page = 0;
vector <Texture> textures;
vector <DataPoint*> viewed; 
vector <DataPoint> train_data;
vector <DataPoint> test_data;
vector <int> test_result;
Classifier * current_classifier;

// class view selection
int selected_class;
Evaluation * cur_eval;
GLUI_Listbox * selected_class_listbox;
vector<int> c_classes;

//Global Glui Objects 
GLUI_StaticText * busytxt;
GLUI * glui;
GLUI * classes;
GLUI * stats;
int ims_per_page = 16;

// main window
size_t window_width;
size_t window_height;
int main_window;
  
  
// Single Image parameters
Texture * singleIm;
size_t image_width; 
size_t image_height;
DataPoint * singleDp;

void quitf(){
  delete currentdb;
  delete singleIm;
  delete singleDp;
  delete busytxt;
  delete glui;
  delete classes;
  delete cur_eval;
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
  main_window = glutCreateWindow( "Image Viewer" );
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
  delete currentdb;
  currentdb = new Dataset(location);
  vector<Category> * cats = currentdb->getCategories();
  size_t c = 0;
  //  classes->add_column(true);
  GLUI_Panel * pan = classes->add_panel("categories");
  if(currentdb != NULL){
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
  glutSetWindow(main_window);
  delete singleIm;
  delete singleDp;
  string url  = askFile();
  singleDp = new DataPoint(0, "", url, ""); 
  singleIm = new Texture(singleDp, main_window);
}

void display(void){
  using namespace states;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  switch(dm){
  case Single_Image:
    if(singleIm!=NULL)
      singleIm->draw(window_height);
    break;
  case Show_Dataset:
    if(currentdb != NULL){
      size_t grid = ceil(sqrt(ims_per_page));
      float scale = 1.0/grid;
      glScalef(scale, scale, 0);
      size_t count  = 0;
      glPushMatrix();
      for(vector<Texture>::iterator it = textures.begin();
	  it != textures.end();
	  ++it){
	it->draw(window_height);
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
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);
  glutPostRedisplay();
  glui->sync_live();
}

void initGlui(){
  glui = GLUI_Master.create_glui( "Control", 0, 800, 0 );
  busytxt = glui->add_statictext( "waiting" ); 
  GLUI_Panel * load_panel = glui->add_panel("load");
  glui->add_button_to_panel(load_panel, "Quit", 0,(GLUI_Update_CB)quitf );
  glui->add_button_to_panel(load_panel, "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  glui->add_button_to_panel(load_panel, "Load Dataset", 0, (GLUI_Update_CB)askDataset );
  glui->add_button_to_panel(load_panel, "Load Caltech", 0, (GLUI_Update_CB)loadCaltech );
  glui->add_column(false);
  GLUI_Panel * view_panel = glui->add_panel("view");
  glui->add_button_to_panel(view_panel, "Refresh", 0, (GLUI_Update_CB)viewDataset );
  glui->add_statictext_to_panel(view_panel, "Images Per Page:" ); 
  glui->add_spinner_to_panel(view_panel, "", GLUI_SPINNER_INT, &ims_per_page);
  glui->add_button_to_panel(view_panel, "Next Page", 0, (GLUI_Update_CB)nextPage );
  GLUI_Listbox * aap = glui->add_listbox_to_panel(view_panel, "view:", (int*) &ds, 0, 
					 (GLUI_Update_CB)viewDataset);
  aap->add_item(states::Enabled_Datasets, "Enabled");
  aap->add_item(states::Training_DataPoints, "Training Set");
  aap->add_item(states::Testing_DataPoints, "Test set");
  aap->add_item(states::Correct, "Correct");
  aap->add_item(states::Incorrect, "Incorr.");
  aap->add_item(states::Particular_Category, "Sel. Cat.");
  selected_class_listbox = glui->add_listbox_to_panel(view_panel, "part. class:", &selected_class, 0, (GLUI_Update_CB)selectAndShow);
  glui->add_column(false);
  GLUI_Panel * ml_panel = glui->add_panel("ML");
  glui->add_button_to_panel(ml_panel, "Get Descriptors", 0, (GLUI_Update_CB)extractFeatures );
  glui->add_button_to_panel(ml_panel, "Evaluate", 0, (GLUI_Update_CB)evaluateClassifier);
  //glui->add_button_to_panel(ml_panel, "Train", 0, (GLUI_Update_CB)train);
  //glui->add_button_to_panel(ml_panel, "Classify", 0, (GLUI_Update_CB)classify);
  glui->set_main_gfx_window(main_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void loadCaltech(){
  loadDataset("/Users/mauricemulder/workspace/datasets/caltech101/");
}

void viewDataset(){
  if(currentdb != NULL){
    dm = states::Show_Dataset;
    setViewSelection();
    refreshTexture(); 
    display();
  }
  page = 0;
}

void setViewSelection(){
  viewed.clear();

  using namespace states;
  if(ds == Enabled_Datasets){
      vector<Category*> enabs = currentdb->getEnabled();
      for(vector<Category*>::iterator cat = enabs.begin(); cat != enabs.end(); ++cat){
	vector<DataPoint> * dps = (*cat)->getDataPoints();
	for(size_t i = 0; i < dps->size(); ++i)
	  viewed.push_back(&dps->at(i));
      }
  }
  if(ds == Training_DataPoints){
    viewed = VisionCore::ptrDeMorgan<DataPoint>(&train_data);
  }

  if(ds == Testing_DataPoints){
    viewed = VisionCore::ptrDeMorgan<DataPoint>(&test_data);
  }
  if(ds == Particular_Category){
    cur_eval->print();
    viewed.clear();
    if(cur_eval != NULL)
      viewed = cur_eval->getInstancesClassifiedAs(selected_class);
  }
  image_width  = window_width / ims_per_page;
  image_height = window_height / ims_per_page;
  refreshTexture();
}

void refreshTexture(size_t p){
  textures.clear();
  for(size_t i = p; i < (size_t) ims_per_page + p && i < (size_t) viewed.size() ; ++i){
    textures.push_back( *new Texture (viewed.at(i), main_window));
  }
  display();
}

void nextPage(){
  page += ims_per_page;
  if(page > viewed.size())
    page = 0;
  refreshTexture(page);
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
  currentdb->rSplit(&train_data, &test_data, 0.5, true);
  delete current_classifier;
  current_classifier = new NNClassifier(1);
  current_classifier->train(&train_data);
  for(vector<int>::iterator cl = c_classes.begin(); 
      cl != c_classes.end(); 
      cl++)
    selected_class_listbox->delete_item(*cl);
  c_classes.clear();
  vector<Category*> enabs = currentdb->getEnabled();
  for(size_t i = 0; i <  enabs.size(); ++i){
	selected_class_listbox->add_item(enabs[i]->getLabel(), 
					 enabs[i]->getName().c_str());
	c_classes.push_back(enabs[i]->getLabel());
    }
}

void classify(){
  if(current_classifier == NULL)
    train();
  test_result = current_classifier->classify(&test_data);
  delete cur_eval;
  cur_eval = new Evaluation(&test_data, &test_result);
  viewDataset();
  showStatistics();
}

void extractFeatures(){
  busytxt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(currentdb);
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
     strstr  << "Instances: " << cur_eval->getInstances() << endl;
     stats->add_statictext(strstr.str().c_str());
   }
   {
     stringstream strstr;
     strstr  << "Correct: " << cur_eval->getCorrect() << endl;
     stats->add_statictext(strstr.str().c_str());
   }
   {
     stringstream strstr;
     strstr  << "Performance: " << cur_eval->getPrecision() << endl;
     stats->add_statictext(strstr.str().c_str());
   }

 }
