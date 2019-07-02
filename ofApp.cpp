#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofEnableDepthTest();
	ofSetLineWidth(3);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());

	auto deg_span = 10;
	for (auto i = 0; i < 20; i++) {

		auto radius = (i + 1) * 7;
		auto width = (i + 1);
		auto noise_seed_x = ofRandom(1000);
		auto noise_seed_z = ofRandom(1000);
		
		ofPushMatrix();
		ofRotateY(ofMap(ofNoise(noise_seed_z, ofGetFrameNum() * 0.0005), 0, 1, -180, 180));
		ofRotateX(ofMap(ofNoise(noise_seed_x, ofGetFrameNum() * 0.0005), 0, 1, -180, 180));

		int deg_start = ofGetFrameNum() * 2 + radius;
		for (auto deg = deg_start; deg < deg_start + 120; deg += deg_span) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), width * 0.5));
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5) * DEG_TO_RAD), width * -0.5));
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), width * -0.5));
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5) * DEG_TO_RAD), width * 0.5));

			ofFill();
			ofSetColor(39, ofMap(deg, deg_start, deg_start + 120, 0, 255));
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}