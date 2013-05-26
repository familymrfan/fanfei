#if !defined CONTROLLER_H
#define CONTROLLER_H

#include "view.h"
#include "model.h"

class Window
{
public:
	void Generate();
private:
	Model model_;
	View view_;
};

#endif // define CONTROLLER_H