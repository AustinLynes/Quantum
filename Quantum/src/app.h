#include "QApplication.h"

class QuantumApp : public QApplication
{
public: 
	QuantumApp();
	~QuantumApp();
	
	int Execute() override;
};

QApplication* CreateApplication()
{
    return new QuantumApp();
}