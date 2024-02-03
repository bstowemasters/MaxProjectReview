#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void draw();
		void keyPressed(int key);
		void mouseMoved(int x, int y );
		void mousePressed(int x, int y, int button);

		// assets needed for drawing 
		ofImage leftOptionImage, rightOptionImage, backgroundImage, gameOverTextAreaImage, populationButton, areaButton, metalGearSolid;
		ofRectangle leftOptionButton, rightOptionButton, gameOverTextAreaButton, choice1, choice2;

		// code needed for changing screens
		enum class screens {home, game, game_over, land, none};
		screens screen;
		
		// stores data from API
		ofxJSONElement json;
		// variables which i used in my code 
		string jsonStringCCA3, jsonStringName, t1, jsonImgString, colour;
		ofImage jsonImg;
		int population, area;
		int x;
		bool updateBoolean;
		char areaOrPopulation;

		string landlocked;
		char landlockedLife;

		int score, highscore;

		int random; // there are 249 countries apparently so 250 gives us 0-249 i think

		ofTrueTypeFont font, font2; // one font for title - one for desc
		string wrappedTextTeaCup, titleText, descriptionText; 

		string ofApp::wrapString(string text, int width, bool headerOrBody); //wrap string code which is taken from https://forum.openframeworks.cc/t/text-wrapping/2953
};
