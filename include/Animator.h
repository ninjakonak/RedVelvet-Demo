#pragma once
#ifndef ANIMATOR_H
#define ANIMATOR_H

#include<iostream>
#include<vector>

class Animator
{

private:
	float frameIndex;
	float frameInc;
	int frameIndexLim;
	bool repeat;
	bool inc = true;
	std::vector<std::string> framesRight;
	std::vector<std::string> framesLeft;
	
	
public:
	Animator(std::vector<std::string> framesRight, std::vector<std::string> framesLeft, bool repeat, float incrementValue);
	std::string changeFrame(int dir);
	void reset();





};

#endif