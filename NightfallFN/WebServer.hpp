#pragma once
#include "crow/crow_all.h"
using namespace crow;

int main()
{
	SimpleApp app;

	CROW_ROUTE(app, "/")
}