#pragma once
#include <iostream>

class Module
{

public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render() {};
	virtual void Destroy() {};

};

