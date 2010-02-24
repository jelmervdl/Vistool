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
Evaluation * cur_eval;


//Global Glui Objects 
GLUI_StaticText * busytxt;
GLUI * glui;
GLUI * classes;
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
  glutInitWindowPosition( 50, 50 );
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
  classes = GLUI_Master.create_glui( "classes", 0, 950, 250 );
  delete currentdb;
  currentdb = new Dataset(location);
  vector<Category> * cats = currentdb->getCategories();
  size_t c = 0;
  classes->add_button( "Print Enabled", 0, (GLUI_Update_CB)test );
  classes->add_button( "Extract Descriptors", 0, (GLUI_Update_CB)extractFeatures );
  classes->add_button( "Train", 0, (GLUI_Update_CB)train);
  classes->add_button( "Classify", 0, (GLUI_Update_CB)classify);
  classes->add_column(true);
  if(currentdb != NULL){
    for(size_t i = 0; i < cats->size(); ++i){
      classes->add_checkbox(
			    (const char *)cats->at(i).getName().c_str(),
			    cats->at(i).getEnabled(),
			    1, (GLUI_Update_CB) NULL);
      c++;
      if(c%34==0)
	classes->add_column(false);
    }
  }
}

void test(){
  currentdb->print();
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
  glui = GLUI_Master.create_glui( "Control", 0, 950, 50 );
  busytxt = glui->add_statictext( "waiting" ); 
  glui->add_button( "Quit", 0,(GLUI_Update_CB)quitf );
  glui->add_button( "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  glui->add_button( "Load Dataset", 0, (GLUI_Update_CB)askDataset );
  glui->add_button( "Load Caltech", 0, (GLUI_Update_CB)loadCaltech );
  glui->add_column(true);
  glui->add_button( "View Dataset", 0, (GLUI_Update_CB)viewDataset );
  glui->add_statictext( "Images Per Page:" ); 
  glui->add_spinner("", GLUI_SPINNER_INT, &ims_per_page);
  glui->add_button( "Next Page", 0, (GLUI_Update_CB)nextPage );
  GLUI_Listbox * aap = glui->add_listbox("view:", (int*) &ds);
  aap->add_item(states::Enabled_Datasets, "Enabled");
  aap->add_item(states::Training_DataPoints, "Training Set");
  aap->add_item(states::Testing_DataPoints, "Test set");
  aap->add_item(states::Correct, "Correct");
  aap->add_item(states::Incorrect, "Incorr.");
  aap->add_item(states::Particular_Category, "Sel. Cat.");
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

void train(){
  extractFeatures();
  train_data.clear();
  test_data.clear();
  currentdb->rSplit(&train_data, &test_data, 0.5, true);
  delete current_classifier;
  current_classifier = new NNClassifier(1);
  current_classifier->train(&train_data);
}

void classify(){
  if(current_classifier == NULL)
    train();
  test_result = current_classifier->classify(&test_data);
  delete cur_eval;
  cur_eval = new Evaluation(&test_data, &test_result);
}

void extractFeatures(){
  busytxt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(currentdb);
  busytxt->set_text("done");
}
