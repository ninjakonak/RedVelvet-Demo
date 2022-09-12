#include "../include/Animator.h"



Animator::Animator(std::vector<std::string> framesRight, std::vector<std::string> framesLeft, bool repeat, float incrementValue) {
	this->framesRight = framesRight;
	this->framesLeft = framesLeft;
	this->frameIndex = 0;
	this->frameIndexLim = size(framesRight);
	this->frameInc = incrementValue;
	this->repeat = repeat;
}

void Animator::reset() {
	this->inc = true;
	this->frameIndex = 0;
}

std::string Animator::changeFrame(int dir) {

	if (dir == 0) {

		if (this->inc) {
			this->frameIndex += this->frameInc;
		}

		if (this->frameIndex >= this->frameIndexLim && repeat) {
			this->frameIndex = 0;
		}

		else if (this->frameIndex >= this->frameIndexLim && !repeat) {
			this->frameIndex = this->frameIndexLim-1;
			this->inc = false;
		}

		return this->framesLeft[int(this->frameIndex)%this->frameIndexLim];
	}

	if (dir == 1) {

		if (this->inc) {
			this->frameIndex += this->frameInc;
		}

		if (this->frameIndex >= this->frameIndexLim&&repeat) {
			this->frameIndex = 0;
		}

		else if(this->frameIndex >= this->frameIndexLim&&!repeat) {
			this->frameIndex = this->frameIndex-1;
			this->inc = false;
		}

		return this->framesRight[int(this->frameIndex) % this->frameIndexLim];
	}
}
