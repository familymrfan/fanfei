#if !defined DIALOG_H
#define DIALOG_H

#include "dialog_model.h"
#include "dialog_view.h"

class Dialog
{
public:
	void Generate();
private:
	DialogModel model_;
	DialogView view_;
};

#endif