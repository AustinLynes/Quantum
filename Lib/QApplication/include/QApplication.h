class QApplication 
{
    public:
        QApplication()
        {
            if (instance != nullptr && instance != this) {
                throw std::runtime_error("Only one instance of QApplication is allowed.");
                delete this;
            } 
            
            instance = this;
        }
        virtual ~QApplication(){}
        
        virtual int Execute() = 0;
    
        static QApplication* GetInstance() {
            return instance;
        }

    private:
        static QApplication* instance;

};

// extern function to be created by the application.
QApplication* CreateApplication();