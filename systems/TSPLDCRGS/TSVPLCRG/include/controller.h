#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

public:
    /*********************************************************
     * 
     * Name:  getInstance
     * Notes: get singleton instance of the controller
     * 
     *********************************************************/
    static Controller *getInstance (void);

    /*********************************************************
     * 
     * Name:  mainLoop
     * Notes: main loop
     * 
     *********************************************************/
    void mainLoop(void);

private:
    
    static Controller *instance;

    /*********************************************************
     * 
     * Name:  Controller
     * Notes: Constructor
     * 
     *********************************************************/
    Controller(void);

    /*********************************************************
     * 
     * Name:  ~Controller
     * Notes: Destructor
     * 
     *********************************************************/
    ~Controller(void);

    /*********************************************************
     * 
     * Name:  init
     * Notes: initialize certain things if needed
     * 
     *********************************************************/
    void init(void);

    // /*********************************************************
    //  * 
    //  * Name:  getSendSOHSerial
    //  * Notes: initialize certain things if needed
    //  * 
    //  *********************************************************/
    // void getSendSOHSerial(void);

    // /*********************************************************
    //  * 
    //  * Name:  rxSerialCommands
    //  * Notes: initialize certain things if needed
    //  * 
    //  *********************************************************/
    // void rxSerialCommands(void);

};

// Not in class

/*********************************************************
 * 
 * Name:  controllerTaskLauncher
 * Notes: Makes isntance of Controller if it doesn't exist
 *        and starts the setup then main loop.
 * 
 *********************************************************/
void controllerTaskLauncher( void *pvParams );

#endif // CONTROLLER_H