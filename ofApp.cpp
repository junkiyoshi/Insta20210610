#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofNoFill();
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->size = 15;
	for (auto x = -450; x <= 450; x += this->size) {

		for (auto y = -450; y <= 450; y += this->size) {

			for (auto z = -450; z <= 450; z += this->size) {

				this->box_info_list.push_back(make_pair(glm::vec3(x, y, z), 0.f));
			}
		}
	}

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	if (ofGetFrameNum() % 30 == 0) {

		auto l = glm::vec3(ofRandom(-350, 350), ofRandom(-350, 350), ofRandom(-350, 350));
		while (glm::distance(l, this->prev_location) < 350) {

			l = glm::vec3(ofRandom(-350, 350), ofRandom(-350, 350), ofRandom(-350, 350));
		}
		auto f = 5;
		this->wave_list.push_back(make_pair(l, f));

		this->prev_location = l;
	}

	for (auto& wave : this->wave_list) {

		for (auto& box_info : this->box_info_list) {

			auto distance = glm::distance(wave.first, box_info.first);
			if (distance > wave.second - 10 && distance < wave.second + 10) {

				box_info.second = (box_info.second >= 1) ? 1 : box_info.second + ofMap(abs(distance - wave.second), 0, 20, 0.125, 0);
			}
		}

		wave.second += 8;
	}

	for (auto& box_info : this->box_info_list) {

		box_info.second = box_info.second < 0 ? 0 : box_info.second - 0.015;
		if (box_info.second > 0) {

			auto box_size = this->size;
			if (box_info.second < 0.03) { box_size = ofMap(box_info.second, 0, 0.03, 0, this->size); }
			this->setBoxToMesh(this->face, this->line, box_info.first, box_size);
		}
	}

	for (int i = this->wave_list.size() - 1; i >= 0; i--) {

		if (this->wave_list[i].second > 350) {

			this->wave_list.erase(this->wave_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.38);

	ofSetColor(39);
	ofNoFill();
	ofDrawBox(900);

	ofSetColor(239);
	this->face.drawFaces();

	ofSetColor(39);
	this->line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& line_target, glm::vec3 location, float size) {

	this->setBoxToMesh(face_target, line_target, location, size, size, size);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& line_target, glm::vec3 location, float height, float width, float depth) {

	int index = face_target.getVertices().size();

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.999, height * 0.5 * 0.999, depth * -0.5 * 0.999));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.999, height * 0.5 * 0.999, depth * -0.5 * 0.999));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.999, height * 0.5 * 0.999, depth * 0.5 * 0.999));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.999, height * 0.5 * 0.999, depth * 0.5 * 0.999));

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.999, height * -0.5 * 0.999, depth * -0.5 * 0.999));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.999, height * -0.5 * 0.999, depth * -0.5 * 0.999));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.999, height * -0.5 * 0.999, depth * 0.5 * 0.999));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.999, height * -0.5 * 0.999, depth * 0.5 * 0.999));

	face_target.addIndex(index + 0); face_target.addIndex(index + 1); face_target.addIndex(index + 2);
	face_target.addIndex(index + 0); face_target.addIndex(index + 2); face_target.addIndex(index + 3);

	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 4); face_target.addIndex(index + 6); face_target.addIndex(index + 7);

	face_target.addIndex(index + 0); face_target.addIndex(index + 4); face_target.addIndex(index + 1);
	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 1);

	face_target.addIndex(index + 1); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 6); face_target.addIndex(index + 2); face_target.addIndex(index + 1);

	face_target.addIndex(index + 2); face_target.addIndex(index + 6); face_target.addIndex(index + 7);
	face_target.addIndex(index + 7); face_target.addIndex(index + 3); face_target.addIndex(index + 2);

	face_target.addIndex(index + 3); face_target.addIndex(index + 7); face_target.addIndex(index + 4);
	face_target.addIndex(index + 4); face_target.addIndex(index + 0); face_target.addIndex(index + 3);

	line_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	line_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	line_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	line_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	line_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	line_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	line_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	line_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	line_target.addIndex(index + 0); line_target.addIndex(index + 1);
	line_target.addIndex(index + 1); line_target.addIndex(index + 2);
	line_target.addIndex(index + 2); line_target.addIndex(index + 3);
	line_target.addIndex(index + 3); line_target.addIndex(index + 0);

	line_target.addIndex(index + 4); line_target.addIndex(index + 5);
	line_target.addIndex(index + 5); line_target.addIndex(index + 6);
	line_target.addIndex(index + 6); line_target.addIndex(index + 7);
	line_target.addIndex(index + 7); line_target.addIndex(index + 4);

	line_target.addIndex(index + 0); line_target.addIndex(index + 4);
	line_target.addIndex(index + 1); line_target.addIndex(index + 5);
	line_target.addIndex(index + 2); line_target.addIndex(index + 6);
	line_target.addIndex(index + 3); line_target.addIndex(index + 7);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}