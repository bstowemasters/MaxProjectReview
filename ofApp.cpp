/*
Comments here
READ ME
Please note that when looking through app it is much easier to debug / test when you can accurately know the answer, therefore I have left in
all of my code which displays the answers on screen but commented it out. These code lines have a "password" next to them.
Simply hold CTRL and hit 'F' and type in:
//YzxNkP99T9WYb8
Removing the comments from these lines will help :)
*/
#include "ofApp.h" // included so my objects and classes and variables work correctly
#include <stdlib.h> // included to i dont have to write STD every time i want to print something 

#include <time.h> // included to give me access to random numbers

ofApp leftObj; // create 2 objects here
ofApp rightObj;

void ofApp::setup(){ // setup code only runs once 
    /*
        API documentation can be found at: https://restcountries.com/
    */
    json.open("https://restcountries.com/v3.1/all"); // opens the api and populates it with the information
    
    //this whole chunk of code needs to be ran once in order to initialise it - im sure there is a better way than copying it to here which avoids code duplication but idk
    leftObj.random = rand() % 250; // generate random integer between 1 and 250
    leftObj.jsonStringCCA3 = json[leftObj.random]["cca3"].asString(); // CCA3 is a naming convention for countries - think of this as a replacement for a countryID (which would have been much easier to work with)
    leftObj.jsonStringName = json[leftObj.random]["name"]["common"].asString();
    leftObj.jsonImgString = json[leftObj.random]["flags"]["png"].asString();
    if (leftObj.jsonStringCCA3 == "ISR") {
        leftObj.jsonImgString = ("C:data\\political.jpg");
    }
    leftObj.jsonImg.load(leftObj.jsonImgString);
    leftObj.area = json[leftObj.random]["area"].asInt();
    leftObj.population = json[leftObj.random]["population"].asInt();
    leftObj.x = 0; // x here is used as either area or population. depending on what the user selects later, thats what x is.

    rightObj.random = rand() % 250;
    rightObj.jsonStringCCA3 = json[rightObj.random]["cca3"].asString();
    rightObj.jsonStringName = json[rightObj.random]["name"]["common"].asString();
    rightObj.jsonImgString = json[rightObj.random]["flags"]["png"].asString();
    if (rightObj.jsonStringCCA3 == "ISR") {
        rightObj.jsonImgString = ("data\\political.jpg");
    }
    rightObj.jsonImg.load(rightObj.jsonImgString);
    rightObj.area = json[rightObj.random]["area"].asInt();
    rightObj.population = json[rightObj.random]["population"].asInt();
    rightObj.x = 0;

    // the following code we only need one copy of - therefore I attached it to the leftObject but this is not relevant.
    leftObj.areaOrPopulation = 'I';
    leftObj.updateBoolean = true;
    leftObj.score = 0;
    leftObj.highscore = 0; // we acc only need 1 of these 
    leftObj.landlocked = json[leftObj.random]["landlocked"].asString(); // for some reason it did not want to pull in a bool - kept giving me a 0
    leftObj.landlockedLife = '1'; // have one life

    // sets the starting screen to home
    screen = screens::home;

    backgroundImage.load("data\\red.png"); // I already had these images from when I was planning and picked the colours so I used them as images instead of drawing a rectangle of colour x - hasnt made a difference so its ok
    gameOverTextAreaImage.load("data\\yellow.png");
    leftOptionImage.load("data\\blue.png");
    rightOptionImage.load("data\\orange.png");

    leftOptionButton.set(0,0,0,0); // dont need them drawn yet since they are not for the home screen so set their information to 0
    rightOptionButton.set(0, 0, 0, 0);
    gameOverTextAreaButton.set(0,0,0,0);
    choice1.set(0, 0, 0, 0);
    choice2.set(0, 0, 0, 0);

    font.load("data\\font.ttf", 28); // this font I used for titles and important info
    titleText = "Welcome to the Higher or Lower Game!";

    font2.load("data\\font.ttf", 16); // this font I used for less important stuff like the description

    descriptionText = "Below are two buttons for slightly different experiences. One of them, the one on the left will start the game with population as the variable. So you need to pick which country you think has the larger population. The other button, the one on the right, uses the area. So you need to pick which country has a larger surface area.";
    wrappedTextTeaCup = wrapString(descriptionText, 1100, false); // this calls wrapString and puts in the description, a width id like to cap it at, and a boolean to decide whether or not its a header. true for header false for not header.

    populationButton.load("data\\blue_population.png");
    areaButton.load("data\\yellow_area.png");
    metalGearSolid.load("data\\mgs.jpg");

    leftObj.colour = ""; // .colour is used to provide user feedback so they know they are selecting one or the other button.
    rightObj.colour = "";

}

void ofApp::draw(){ // anything which needs to be represented in the GUI should be in this draw area.
    // set color to white this ensures no tint is placed on image which is drawn next
    ofSetColor(255);
    // this if checks to see what current screen the user is on. there will be a lot of these since they are essential conditions for which code can be applied on. 
    if (screen == screens::home) {
        backgroundImage.draw(0, 0, 1200, 750); // this should cover the whole home screen at all times
        leftObj.landlockedLife = '1'; // resets number of lives back to 1 - change this to whatever number you want if you want more lives but 1 is enough i reckon
        font.drawString(wrapString(titleText, 1100, true), 50, 100); // there are 2 calls here being made. one is to wrap the string, the other is to take the string which is now wrapped and display it on the GUI
        font2.drawString(wrappedTextTeaCup, 50, 200);
        
        choice1.set(200, 400, 250, 175); // where you see 4 numbers like this they generally represent xPos, yPos, width and height relative to (0,0), which is the top left corner
        choice2.set(700, 400, 250, 175);
        
        ofDrawRectangle(choice1);
        ofDrawRectangle(choice2);

        populationButton.draw(200, 400, 250, 175);
        areaButton.draw(700, 400, 250, 175);
    }
    else if (screen == screens::game) {
        backgroundImage.draw(0, 0, 1200, 750); // this should cover the whole game screen at all times

        leftOptionImage.draw(0, 0, 600, 750);
        font.drawString(wrapString(leftObj.jsonStringName, 550, true), 50, 65);
        //ofDrawBitmapString(leftObj.population, 20, 500); //YzxNkP99T9WYb8
        //ofDrawBitmapString(leftObj.area, 20, 525); //YzxNkP99T9WYb8
        leftObj.jsonImg.draw(0, 130, 600, 300); //this does not work since not all flags are the same shape - for example switzerland's flag is square not rectangular

        rightOptionImage.draw(600, 0, 600, 750);
        font.drawString(wrapString(rightObj.jsonStringName, 550, true), 650, 65);
        //ofDrawBitmapString(rightObj.population, 620, 500); //YzxNkP99T9WYb8
        //ofDrawBitmapString(rightObj.area, 620, 525); //YzxNkP99T9WYb8
        rightObj.jsonImg.draw(600, 130, 600, 300); 


        leftOptionButton.set(0, 0, 600, 750);
        rightOptionButton.set(600, 0, 600, 750);

        // score drawn last as it is going to cover both sides of the screen and this has a first come first served basis for drawing. whatever is drawn first ends up on the bottom. and by bottom i OF COURSE mean farthest away from the camera on the z-axis
        font.drawString("Score:", 450, 550); // will not need to wrap the score since ppl unlikely to get a score worthy of being wrapped
        font.drawString(ofToString(leftObj.score), 640, 550); // need ofToString to convert it quickly to a string so it is valid - found that here - https://openframeworks.cc/documentation/graphics/ofGraphics/#show_ofToString

        ofSetColor(208, 72, 72);

        if (leftObj.colour != "left") { // if the mouse is hovering over your option, then redraw the name of said option in a different colour - thats all this is doing but it provides a nice affect
            font.drawString(wrapString(leftObj.jsonStringName, 550, true), 50, 65);
        }
        if (rightObj.colour != "right") {
            font.drawString(wrapString(rightObj.jsonStringName, 550, true), 650, 65);
        }
        ofSetColor(255); // reset colour back to white - likely dont need this as it is also at the start of the draw function but may cause issues when using keys to move between screens if removed
    }
    else if (screen == screens::game_over) {
        backgroundImage.draw(0, 0, 1200, 750); // this should cover the whole game over screen at all times
        metalGearSolid.draw(300, 200, 600, 300); // SNAKEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE - should have looked to see if i could put videos or sound in omds
        gameOverTextAreaButton.set(300, 200, 600, 300); // this button takes you back to the main menu

        font.drawString(ofToString(leftObj.score), 450, 100); // score is the score that you just accumulated 
        font.drawString("Score:", 300, 100);

        font.drawString(ofToString(leftObj.highscore), 525, 150); // highscore is the best score you have acheived since running the app. will reset when app closes
        font.drawString("Highscore:", 300, 150);
    }
    else if (screen == screens::land) { // after adding this i looked up how many countries are landlocked vs arent and theres way more which arent so this is like a free life every time - still works tho 
        gameOverTextAreaImage.draw(0, 0, 1200, 750); // this should cover the whole land screen at all times - changed to use the gameOver image here bc i wanted the yellow even tho this isnt the proper way of doing thatbla bla bla
        ofSetColor(0);
        font.drawString("Ah, you got that wrong!", 50, 100); // L
        font2.drawString("But you'll get a second chance if you can say whether or not:", 50, 200);
        font2.drawString(ofToString(leftObj.jsonStringName), 680, 200);
        font2.drawString("is landlocked. Press 'T' for true, 'F' for false.", 50, 250); // not sure if there is an easier way of doing this - i couldnt figure one out so this text is split across 3 lines
        
        //ofDrawBitmapString(leftObj.landlocked, 50, 500); //YzxNkP99T9WYb8
    
    }
    else if (screen == screens::none) {
        cout << "loading";
    }
    else { // when the user clicks on the land screen it runs this but it doesnt break the code or slow it down or anything so its staying.
        cout << "Something has gone horribly wrong - but dont worry it doesnt matter :)" << endl;
    }
}

void ofApp::keyPressed(int key){
    // code which should run when the user has to pick whether a country is landlocked or not 
    if (screen == screens::land && (key == 'T' || key == 't')) {
        //user thinks its landlocked
        if (leftObj.landlocked == "true") {
            //correct
            screen = screens::game;
        }
        else {
            screen = screens::game_over;
        }
    }
    else if (screen == screens::land && (key == 'F' || key == 'f')) { // will not be on a key press
        //user thinks its not landlocked
        if (leftObj.landlocked == "false") {
            //correct
            screen = screens::game;
        }
        else {
            screen = screens::game_over;
        }
    }
    // testing - might keep these as they are useful but not acc supposed to be used in a fair game:
    // decided to keep them in but comment them out so users can easily uncomment if they want to test anything
    /* //YzxNkP99T9WYb8
    if (key == 'h') {
        cout << key;
        screen = screens::home;

    }
    else if (key == 'g') {
        cout << key;
        screen = screens::game;

    }
    else if (key == 'o') {
        cout << key;
        screen = screens::game_over;
    }
    else if (key == 'l') {
        cout << key;
        screen = screens::land;
    }
    */ //YzxNkP99T9WYb8
}

void ofApp::mouseMoved(int x, int y ){
    // checks to see which choice a user is hovering thieir mouse over and uses this to decide which side to highlight with a colour way back up in the draw area
    if (screen == screens::game) {
        if (x > 600) {
            leftObj.colour = "left";
            rightObj.colour = "";
        }
        else if (x <= 600) {
            rightObj.colour = "right";
            leftObj.colour = "";
        }
    }
}

void ofApp::mousePressed(int x, int y, int button){
    // user makes a decision with their mouse - by pressing a button - doesnt matter which button.
    if (screen == screens::home) {
        if (choice1.inside(x,y)) { // population 
            //here we set the variables for the game so that it searches for one thing - in this case i used population
            leftObj.areaOrPopulation = 'P';
            leftObj.x = leftObj.population;
            rightObj.x = rightObj.population;
            cout << endl << "leftObj" << leftObj.x << endl;
            cout << endl << "rightObj" << rightObj.x << endl;
            leftObj.score = 0; // if the user has made it to the home screen it means they have either just started or just lost a game - either way - their score should be 0
            screen = screens::game;
        }
        else if (choice2.inside(x, y)) { // area
            //here we set the variables for the game so that it searches for another thing - in this case i used area
            leftObj.areaOrPopulation = 'A';
            leftObj.x = leftObj.area;
            rightObj.x = rightObj.area;
            cout << endl << "leftObj" << leftObj.x << endl;
            cout << endl << "rightObj" << rightObj.x << endl;
            leftObj.score = 0;
            screen = screens::game;
        }
    }
    else if (screen == screens::game) {
        if (leftObj.updateBoolean == true) { // this dictates whether or not the game is still being played or if the player has lost
            if (leftObj.areaOrPopulation == 'P') { // this if else combo simply makes x whatever it needs to be. x is the variable in which decisions of which number is bigger than the other are made.
                leftObj.x = leftObj.population;
                rightObj.x = rightObj.population;
            }
            else if (leftObj.areaOrPopulation == 'A') {
                leftObj.x = leftObj.area;
                rightObj.x = rightObj.area;
            }
            // resets all of the variables for the left object
            leftObj.random = rand() % 250;
            leftObj.jsonStringCCA3 = json[leftObj.random]["cca3"].asString();
            leftObj.jsonStringName = json[leftObj.random]["name"]["common"].asString();
            leftObj.jsonImgString = json[leftObj.random]["flags"]["png"].asString();
            if (leftObj.jsonStringCCA3 == "ISR") {
                leftObj.jsonImgString = ("data\\political.jpg");
            }
            leftObj.jsonImg.load(leftObj.jsonImgString);
            leftObj.area = json[leftObj.random]["area"].asInt();
            leftObj.population = json[leftObj.random]["population"].asInt();
            // resets all of the variables for the right object
            rightObj.random = rand() % 250;
            rightObj.jsonStringCCA3 = json[rightObj.random]["cca3"].asString();
            rightObj.jsonStringName = json[rightObj.random]["name"]["common"].asString();
            rightObj.jsonImgString = json[rightObj.random]["flags"]["png"].asString();
            if (rightObj.jsonStringCCA3 == "ISR") {
                rightObj.jsonImgString = ("data\\political.jpg");
            }
            rightObj.jsonImg.load(rightObj.jsonImgString);
            rightObj.area = json[rightObj.random]["area"].asInt();
            rightObj.population = json[rightObj.random]["population"].asInt();
            // resets the landlocked which is for the left object but doesnt need to be
            leftObj.landlocked = json[leftObj.random]["landlocked"].asString();


            updateBoolean = false;
        }


        if (leftOptionButton.inside(x, y)) { // originally i had the if statement check for the screen then realised id have to do that with every check so now i have the states under if statements which makes it easier
            // Left button clicked
            if (leftObj.x > rightObj.x || leftObj.x == rightObj.x) { // checks to see which side "wins" or if there is a "draw"
                leftObj.score++; // increase the score
                updateBoolean = true; // allow user to play another round
            }
            else{
                if (leftObj.score > leftObj.highscore) {
                    leftObj.highscore = leftObj.score;
                }
                updateBoolean = false; // user doesnt play another round since they lost unless...
                if (leftObj.landlockedLife == '1') { // ...they have their life still. if they do...
                    leftObj.landlockedLife = '0'; // ...its consumed and they are...
                    screen = screens::land; // ...asked the true or false question about a countries landlocked status. if they dont...
                }
                else {
                    screen = screens::game_over; // ...the game ends here for them.
                }
            }
        }
        if (rightOptionButton.inside(x, y)) {
            // Right button clicked -- largely does the same thing but in reverse
            if (leftObj.x < rightObj.x || leftObj.x == rightObj.x) {
                leftObj.score++;
                updateBoolean = true;
            }
            else {
                if (leftObj.score > leftObj.highscore) {
                    leftObj.highscore = leftObj.score;
                }
                updateBoolean = false;
                //originally had the score reset to 0 here but acc need it to still show score on gameover screen so moved it to the start of the game.
                if (leftObj.landlockedLife == '1') {
                    leftObj.landlockedLife = '0';
                    screen = screens::land;
                }
                else {
                    screen = screens::game_over;
                }
            }
        }
        
    }
    else if (screen == screens::game_over) { // not much to do on a game over screen except go back to the main menu and try again
        if (gameOverTextAreaButton.inside(x, y)) {
            //cout << "text button clicked" << endl;
            screen = screens::home;
        }

    }
    else if (screen == screens::none) {
        cout << "loading";
    }
    else {
        cout << "Something has gone horribly wrong";
    }
}
// this wrapString code is taken from openframeworks user vanderlin whos profile can be found here: https://forum.openframeworks.cc/u/vanderlin
// i have made some adjustments so that this code can be used for header or body fonts. i added the boolean headerOrBody to check this.
string ofApp::wrapString(string text, int width, bool headerOrBody) {
    string typeWrapped = "";
    string tempString = "";
    vector <string> words = ofSplitString(text, " "); //create vector full of individual words in string passed in

    for (int i = 0; i < words.size(); i++) { //run through vector
        string wrd = words[i]; //get current word in vector

        // if we aren't on the first word, add a space
        if (i > 0) {
            tempString += " ";
        }
        tempString += wrd; //add current word to temp string

        int stringWidth = -1;

        if (headerOrBody == true) { // true for header and false for body
            stringWidth = font.stringWidth(tempString); //set string width to length of line
        }
        else {
            stringWidth = font2.stringWidth(tempString); //set string width to length of line
        }

        if (stringWidth >= width) {//check string with to add either space or new line before current word
            typeWrapped += "\n"; //if line is now longer than desired width add a new line
            tempString = wrd; // make sure we're including the extra word on the next line
        }
        else if (i > 0) {
            typeWrapped += " "; // if we aren't on the first word, add a space
        }
        typeWrapped += wrd; //add current word to string to be returned with new lines for wrapping
    }
    return typeWrapped;
}
// wrap text:
// https://forum.openframeworks.cc/t/text-wrapping/2953