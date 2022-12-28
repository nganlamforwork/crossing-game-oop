#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>

#include "COMMON.h"

class GUI {
private:
public:
	static void MainTitle(int, int);
	static void Image(string, int, int, int);
};