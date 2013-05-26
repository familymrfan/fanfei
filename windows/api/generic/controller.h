#if !defined CONTROLLER_H
#define CONTROLLER_H

#include "view.h"
#include "model.h"

class Controller
{
public:
	void Generate();
private:
	Model model_;
	View view_;
};

#endif // define CONTROLLER_H