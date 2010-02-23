#include "gluiVisionTool.h"

using namespace std;

enum DisplayMode {
  Nothing,
  Single_Image,
  Show_Dataset
};

DisplayMode dm = Single_Image;

GLUI_StaticText * busytxt;
GLUI * glui;
GLUI * classes;

int ims_per_page = 10;
Texture * singleIm;

size_t page = 0;

Dataset * currentdb;
DataPoint * singleDp;

size_t window_width = 100;
size_t window_height = 100;
int main_window;

 size_t image_width  = window_width / ims_per_page;
size_t image_height = window_height / ims_per_page;

vector <Texture> textures;
vector <DataPoint*> viewed; 

void quitf(){
  delete currentdb;
  delete singleIm;
  delete singleDp;
  delete busytxt;
  delete glui;
  delete classes;
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
  classes->add_column(true);
  if(currentdb != NULL){
    for(size_t i = 0; i < cats->size(); ++i){
      classes->add_checkbox(
			    (const char *)cats->at(i).getName().c_str(),
			    cats->at(i).getEnabled(),
			    1, (GLUI_Update_CB) NULL);
      c++;
      if(c%20==0)
	classes->add_column(false);
    }
  }
}

void extractFeatures(){
  busytxt->set_text("extracting...");
  glutPostRedisplay();
  FeatureExtractor * f = FeatureExtractor::getInstance();
  f->saveDescriptorsToFile(currentdb);
  busytxt->set_text("done");
}

void test(){
  currentdb->print();
}

void loadPicture(){
  dm = Single_Image;
  glutSetWindow(main_window);
  delete singleIm;
  delete singleDp;
  string url  = askFile();
  singleDp = new DataPoint(0, "", url, ""); 
  singleIm = new Texture(singleDp, main_window);
}

void display(void){
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
  glui->add_statictext( "Vision Tool" ); 
  busytxt = glui->add_statictext( "waiting" ); 
  glui->add_button( "Quit", 0,(GLUI_Update_CB)quitf );
  glui->add_button( "Load Picture", 0, (GLUI_Update_CB)loadPicture );
  glui->add_button( "Load Dataset", 0, (GLUI_Update_CB)askDataset );
  glui->add_button( "Load Caltech", 0, (GLUI_Update_CB)loadCaltech );
  glui->add_button( "View Dataset", 0, (GLUI_Update_CB)viewDataset );
  glui->add_spinner("images per page", GLUI_SPINNER_INT, &ims_per_page);
  glui->add_button( "Next Page", 0, (GLUI_Update_CB)nextPage );
  glui->set_main_gfx_window(main_window);
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
}

void loadCaltech(){
  loadDataset("/Users/mauricemulder/workspace/datasets/caltech101/");
}

void viewDataset(){
  if(currentdb != NULL){
    setViewSelection();
    dm = Show_Dataset;
    display();
  }
  page = 0;
}

void setViewSelection(){
  viewed.clear();
  size_t j = 0;
  vector<Category*> enabs = currentdb->getEnabled();
  for(vector<Category*>::iterator cat = enabs.begin(); cat != enabs.end(); ++cat){
    vector<DataPoint> * dps = (*cat)->getDataPoints();
    for(size_t i = 0; i < dps->size(); ++i){
      viewed.push_back(&dps->at(i));
      cout << viewed.at(j)->getImageURL() << endl;
      j++;
    }
  }
  image_width  = window_width / ims_per_page;
  image_height = window_height / ims_per_page;
  refreshTexture();
}

void refreshTexture(size_t p){
  textures.clear();
  for(size_t i = p; i < (size_t) ims_per_page + p && i < (size_t) viewed.size() ; ++i){
    cout << i << endl;
    cout << i << " " << viewed.size() << viewed.at(i)->getImageURL() << endl;
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
