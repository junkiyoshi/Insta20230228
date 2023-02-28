#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		this->radius_list[i] += this->speed_list[i];

		if (this->radius_list[i] > this->max_radius_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->radius_list.erase(this->radius_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_radius_list.erase(this->max_radius_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for(int i = 0; i < 2; i++) {

		int random_deg = (ofGetFrameNum() * 3) % 360 + ofRandom(-10, 10);
		int random_radius = 250 + ofRandom(-60, 60);

		auto location = glm::vec2(random_radius * cos(random_deg * DEG_TO_RAD), random_radius * sin(random_deg * DEG_TO_RAD));
		this->location_list.push_back(location);
		this->radius_list.push_back(1);
		this->speed_list.push_back(ofRandom(0.2, 0.5));
		this->max_radius_list.push_back(ofRandom(15, 30));
		color.setHsb(ofMap(location.x, -310, 310, 0, 255), 255, 255);
		this->color_list.push_back(color);
	}

	this->line.clear();
	for (int i = 0; i < this->location_list.size(); i++) {

		this->line.addVertex(glm::vec3(this->location_list[i], 0));

		auto alpha = this->radius_list[i] < this->max_radius_list[i] * 0.5 ? 255 : ofMap(this->radius_list[i], this->max_radius_list[i] * 0.5, this->max_radius_list[i], 255, 0);
		this->line.addColor(ofColor(this->color_list[i], alpha));
		this->color_list[i] = ofColor(this->color_list[i], alpha);
	}

	for (int i = 0; i < this->line.getNumVertices(); i++) {

		for (int k = i + 1; k < this->line.getNumVertices(); k++) {

			if (this->radius_list[i] > 2 && this->radius_list[k] > 2) {

				auto distance = glm::distance(this->line.getVertex(i), this->line.getVertex(k));

				if (distance < 40) {

					this->line.addIndex(i);
					this->line.addIndex(k);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->line.drawWireframe();
	for (int i = 0; i < this->location_list.size(); i++) {

		ofSetColor(this->color_list[i]);

		ofNoFill();
		ofDrawCircle(this->location_list[i], this->radius_list[i]);

		ofFill();
		ofDrawCircle(this->location_list[i], 2);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}