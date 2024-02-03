#include "ofMain.h"
#include "ofApp.h"

int main( ){
	ofSetupOpenGL(1200,750,OF_WINDOW); // makes a window of the exact size i need

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
