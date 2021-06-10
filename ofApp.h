#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void setBoxToMesh(ofMesh& face_target, ofMesh& line_target, glm::vec3 location, float size);
	void setBoxToMesh(ofMesh& face_target, ofMesh& line_target, glm::vec3 location, float height, float width, float depth);

	vector<pair<glm::vec3, float>> box_info_list;
	vector<pair<glm::vec3, float>> wave_list;
	glm::vec3 prev_location;
	float size;

	ofEasyCam cam;
	ofMesh face, line;
};