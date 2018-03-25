/*  +---------------------------------------------------------------------------+
*  |                                                                           |
*  | Fluicell AB, http://fluicell.com/                                         |
*  | Lab-on-a-tip 2.0                                                          |
*  |                                                                           |
*  | Authors: Mauro Bellone - http://www.maurobellone.com                      |
*  | Released under GNU GPL License.                                           |
*  +---------------------------------------------------------------------------+ */


#ifndef Labonatip_GUI_H_
#define Labonatip_GUI_H_

// standard libraries
#include <iostream>
#include <string>

// autogenerated form header
#include "ui_Lab-on-a-tip.h"

// Qt
#include <QMainWindow>
#include <QTranslator>
#include <QDateTime>
#include <QTimer>
//#include <QWhatsthis>
#include <qwhatsthis.h>
#include <QException>

// QT for graphics
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>


#include "Q_DebugStream.h"
#include "tools.h"
#include "protocolEditor.h"
#include "protocolRunner.h"
#include "chart.h"

// serial
#include <serial/serial.h>
// PPC1api 
#include <fluicell/ppc1api/ppc1api.h>


using namespace std;

// new shorter class name = Lab-on-a-tip  -- Loat 
class Labonatip_GUI : public QMainWindow
{
	Q_OBJECT

public:
	explicit Labonatip_GUI(QMainWindow *parent = nullptr);

	~Labonatip_GUI();
	
	/**  Set the version of the software from the main 
	*
	*/
	void setVersion(string _version);

	void setProtocolUserPath(QString _path) { m_protocol_path = _path; }

	void setSettingsUserPath(QString _path) { m_settings_path = _path; }

	void setExtDataUserPath(QString _path) { m_ext_data_path = _path;  }

	/** \brief This function is called when the down arrow on Pon is called
	*        it decreases the pressure on Pon, it does not accept out-of-range
	*
	* \note
	*/
	void updatePonSetPoint(double _pon_set_point);

	/** \brief This function is called when the down arrow on Pon is called
	*        it decreases the pressure on Pon, it does not accept out-of-range
	*
	* \note
	*/
	void updatePoffSetPoint(double _poff_set_point);

	/** \brief This function is called when the down arrow on Pon is called
	*        it decreases the pressure on Pon, it does not accept out-of-range
	*
	* \note
	*/
	void updateVrecircSetPoint(double _v_recirc_set_point);

	/** \brief This function is called when the down arrow on Pon is called
	*        it decreases the pressure on Pon, it does not accept out-of-range
	*
	* \note
	*/
	void updateVswitchSetPoint(double _v_switch_set_point);

private slots:

	/** \brief This function is called when the down arrow on Pon is called
	  *        it decreases the pressure on Pon, it does not accept out-of-range
	  *
	  * \note
	  */
	void pressurePonDown();

	/** \brief This function is called when the up arrow on Pon is called
	  *        it increases the pressure on Pon, it does not accept out-of-range
	  *
	  * \note
	  */
	void pressurePonUp();

	/** \brief This function is called when the down arrow on Poff is called
	  *        it decreases the pressure on Poff, it does not accept out-of-range
	  *
	  * \note
	  */
	void pressurePoffDown();

	/** \brief This function is called when the up arrow on Poff is called
	*          it increases the pressure on Poff, it does not accept out-of-range
	*
	* \note
	*/
	void pressurePoffUp();

	/** \brief This function is called when the down arrow on v_switch is called
	*          it decreases the vacuum, it does not accept out-of-range
	*
	* \note
	*/
	void pressButtonPressed_switchDown();

	/** \brief This function is called when the up arrow on v_switch is called
	*          it increases the vacuum, it does not accept out-of-range
	*
	* \note
	*/
	void pressButtonPressed_switchUp();


	/** \brief This function is called when the down arrow on v_recirc is called
	*          it decreases the vacuum, it does not accept out-of-range
	*
	* \note
	*/
	void recirculationDown();

	/** \brief This function is called when the up arrow on v_recirc is called
	*          it increases the vacuum, it does not accept out-of-range
	*
	* \note
	*/
	void recirculationUp();


	/** \brief Update macro status message
	*
	* \note
	*/
	void updateMacroStatusMessage(const QString &_message);

	/** \brief Update macro time status for the chart
	*
	* \note
	*/	
	void updateMacroTimeStatus(const double &_status);

	/** \brief Ask message
	*
	* \note
	*/
	void askMessage(const QString &_message);

	void colSolution1Changed(const int _r, const int _g, const int _b);

	void colSolution2Changed(const int _r, const int _g, const int _b);

	void colSolution3Changed(const int _r, const int _g, const int _b);

	void colSolution4Changed(const int _r, const int _g, const int _b);

	/** \brief Stop all pumps and close the valves
	   *
	   * \note
	   */
	void pumpingOff();

	/** \brief Close the valves
	*
	* \note
	*/
	void closeAllValves();


	/** \brief pushSolution1
	*
	* \note
	*/
	void pushSolution1();

	/** \brief  pushSolution2
	*
	* \note
	*/
	void pushSolution2();

	/** \brief pushSolution3
	*
	* \note
	*/
	void pushSolution3();

	/** \brief pushSolution4
	*   //TODO: add an argument for all 1-4 _activate 
	*           if _activate = true, solution flow start
	*           if _activate = false, solution flow stop
	* \note
	*/
	void pushSolution4();

	/** \brief Set current pressure/vacuum values as 100% default values
	*
	* \note
	*/
	void setAsDefault();

	/** \brief Increase/reduce the area for the solution depiction
	*
	* \note
	*/
	void sliderPonChanged(int _value);


	void switchLanguage(int _value);


	/** \brief Set debug to terminal
	*
	* \note
	*/
	void dumpToTerminal(int _state) {
		qout->copyOutToTerminal(_state);  
		qerr->copyOutToTerminal(_state);
	};


	/** \brief Set debug to terminal
	*
	* \note
	*/
	//void setPpc1Verbose(int _state) {
	//	m_ppc1->setVerbose(_state);
	//};

	/** \brief Increase/reduce the area for the solution depiction
	*
	* \note
	*/
	void sliderPoffChanged(int _value);

	/** \brief Increase/reduce the area for the solution depiction
	*
	* \note
	*/
	void sliderRecircChanged(int _value);

	/** Increase/reduce the area for the solution depiction
	*
	* \note
	*/
	void sliderSwitchChanged(int _value);

	/** \brief This is supposed to be used from the solution release time to
	  * update the visualization of the circular sliders
	  *
	  * \note
	  */
	void updateTimingSliders( );

	void updateFlows();

	void updateGUI();

	void updateWaste();

	void updateWells();

	/** \brief Visualize a message and a progress bar 
	* \note
	*/
	bool visualizeProgressMessage(int _seconds, QString _message = " no message ");

	/** \brief  Enter what's this mode
	  * \note
	  */
	void  ewst();

	void cleanHistory();

	/** \brief Visualize the about dialog
	  * \note
	  */
	void  about();

	void toolEmptyWells();

	void toolRefillSolution();

	/** \brief Catch ok signal from tool dialog
	* \note
	*/
	void toolOk();

	/** \brief Catch apply signal from tool dialog
	* \note
	*/
	void toolApply();

	void editorOk();

	void editorApply();

//DELIVERY

	/** \brief This function is called when the button + on droplet size is clicked
	*
	*   only Pon and V_recirc + - 2.5%
	*
	* \note
	*/
	void dropletSizePlus();

	/** \brief This function is called when the button - on droplet size is clicked
	*
	*   only Pon and V_recirc + - 2.5%
	*
	* \note
	*/
	void dropletSizeMinus();


	/** \brief This function is called when the button + on flow speed is clicked
	*
	*   	 +5% to all values
	*	 Poff does not read too low values,
	*	 if 5% different is less than 5 mbar .... start -> start + 5 --> start - 5%
	*
	* \note
	*/
	void flowSpeedPlus();

	/** \brief This function is called when the button - on flow speed is clicked
	*
	*   	 -5% to all values
	*	 Poff does not read too low values,
	*	 if 5% different is less than 5 mbar .... start -> start + 5 --> start - 5%
	*
	* \note
	*/
	void flowSpeedMinus();

	/** \brief This function is called when the button + on flow speed is clicked
	*
	*   	 +5% v_recirculation
	*
	* \note
	*/
	void vacuumPlus();

	/** \brief This function is called when the button - on flow speed is clicked
	*
	*   	 -5% v_recirculation
	*
	* \note
	*/
	void vacuumMinus();

	/** \brief Update flow control percentages
	*
	*   Only in simulation recalculate the percentages according to the same method in the PPC1 api
	*
	* \note
	*/
	void updateFlowControlPercentages();


//END DELIVERY


//TOOLSACTIONS

	/** \brief Open a setting file
	* 
	*   Open a setting file from a user folder
	*  
	* \note
	*/
	void openSettingsFile();

	/** \brief save the settings to a file
	*
	*   Save the current settings to a .ini file in the user folder
	*
	* \note
	*/
	void saveSettingsFile();

	/** \brief This function shows a tool dialog,
	*        all the settings must be implemented here
	*
	* \note
	*/
	void showToolsDialog();


	/** \brief This function shows a protocol editor dialog,
	*       
	*
	* \note
	*/	void showProtocolEditorDialog();


	/** \brief Enter simulation mode - the PPC1 will not be used
	* \note
	*/
	void simulationOnly();

	/** \brief Connect and disconnect the PPC1
	*
	*   //TODO: add an argument _connect = true to connect, false to disconnect
	*   //DONE: deprecated ---- remove after testing
	* \note
	*/
	//void disCon();

	/** \brief Connect and disconnect the PPC1
	*
	*   \param _connect = true to connect, false to disconnect
	*
	* \note
	*/
	bool disCon(bool _connect);
	
	/** \brief Reboot the PPC1
	*
	* \note This is a hard reboot for the PPC1 device,
	*       it will cause the disconnection from the serial port
	*/
	void reboot();

	/** \brief Run the shutdown procedure
	*
	* \note
	*/
	void shutdown();

	/** \brief Open/close the dock for advaced tools
	*
	* \note
	*/
	void closeOpenDockTools();

	void resizeToolbar();

//END TOOLSACTIONS

//PPC1ACTIONS:

	/** \brief The operation run in background, a signal is emitted at the end
	*
	* \note
	*/
	void newTip();


	/** \brief The operation run in background, a signal is emitted at the end
	*
	* \note
	*/
	void runMacro();


	/** \brief The operation run in background, a signal is emitted at the end
	*
	* \note
	*/
	void macroFinished(const QString &_result);

	/** \brief Run --- still work in progress
	*
	*    It will put the device into the operational mode by running the following macro
	*      allOff()
	*      setPoff(21)
	*      setPon(190)
	*      setVswitch(-115)
	*      setVrecirc(-115)
	*
	*
	* \note
	*/
	void operationalMode();

	/** \brief Stop solution flow
	*
	*   Stop the flow of the solution if one of the solutions is flowing
	*
	*
	* \note
	*/
	void stopSolutionFlow();


	/** \brief  Put the device into a standby mode
	*
	*       Put the device into a standy mode by running the following commands:
	*
	*       STANDBY MACRO
	*       allOff()
	*       setPoff(11)
	*       setPon(0)
	*       sleep(5)
	*       setVswitch(-45)
	*       setVrecirc(-45)
	*
	* \note
	*
	*/
	void standby();

//END PPC1ACTIONS

protected:
	// event control
	void closeEvent(QCloseEvent *event); 
	
	void changeEvent(QEvent*);

	void resizeEvent(QResizeEvent*);

	bool eventFilter(QObject *_obj, QEvent *_event);

private:

	void setEnableMainWindow(bool _enable = false);

	void setEnableSolutionButtons(bool _enable = false);

	QString generateStyleSheet(const QColor _color) {
		return generateStyleSheet(_color.red(), _color.green(), _color.blue());
	}

	QString generateStyleSheet(const int _r, const int _g, const int _b);

	// save log data, messages from the console ect. 
	void dumpLogs();

  /** Increase/reduce the area for the solution depiction
  *  
  * \note
  */
  void updateDrawing(int _value);

  /** set status led to connect or disconnect
  *
  */
  void setStatusLed( bool _connect = false );

  /** group all the connects are in this function
  *
  */
  void initConnects();

  /** group all the connects are in this function
  *
  */
  void initCustomStrings();

  Ui::Labonatip_GUI *ui;               //!< the main user interface
  Labonatip_tools * m_dialog_tools;    //!< pointer to the tools dialog
  Labonatip_protocol_editor * m_dialog_p_editor; //!< pointer to the protocol editor dialog

  QDebugStream *qout;                 //!< redirect cout for messages into the GUI
  QDebugStream *qerr;                 //!< redirect cerr for messages into the GUI

  //settings
  COMSettings *m_comSettings;         //!< communication settings
  solutionsParams *m_solutionParams;  //!< solution parameters, names a default values
  pr_params *m_pr_params;             //!< pressure and vacuum parameters
  GUIparams *m_GUI_params;            //!< GUI parameters

  pipetteStatus *m_pipette_status;    //!< pipette status in terms of pressures, vacuum and flows

  // for serial communication with PPC1 API
  fluicell::PPC1api *m_ppc1;  //!< object for the PPC1api connection
  std::vector<fluicell::PPC1api::command> *m_protocol;   //!< this is the current protocol to run

  bool m_pipette_active;    //!< true when the pipette is active and communicating, false otherwise
  bool m_simulationOnly;    //!< if active the software will run without the hardware device connected
  
  // Threding for protocols and update GUI
  Labonatip_macroRunner *m_macroRunner_thread;
  QTimer *m_update_flowing_sliders;        //!< connected to an update visualization function relative to solutions flow
  QTimer *m_update_GUI;                    //!< update GUI to show PPC1 values
  QTimer *m_update_waste;                  //!< update GUI to show PPC1 values
  const int m_base_time_step;              //!< used to set the update timers, every step is by default 1000 ms
  int m_flowing_solution;                  //!< needed for the visualization function relative to solution 1 - 2 - 3- 4

  //!< set the multiplicators for the time step, 
  //    e.g. desired_duration (sec) = multiplicator * m_base_time_step (100ms)
  //    TODO: KNOWN ISSUE: timing is not well fulfilled --- it is longer than expected
  int m_time_multipilcator;           //!< used to set the update time for the timers
  int m_timer_solution;               //!< duration of injection for solution 
  double m_protocol_duration;         //!< this is the timeline for the protocol execution
  
  //GUI stuff for drawing solution flow
  QGraphicsScene *m_scene_solution;   //!< scene to draw the solution flow
  QPen m_pen_line;                    //!< pen to draw the solution inside the pipe
  const int m_pen_line_width;         //!< pen line width, value = 5
  const float l_x1;                   //!< x-coordinate of the line starting point, value = -18.0
  const float l_y1;                   //!< y-coordinate of the line starting point, value = 49.0  
  const float l_x2;                   //!< x-coordinate of the line ending point, value = 55.0  
  const float l_y2;                   //!< y-coordinate of the line ending point, value = l_y1

  QColor m_sol1_color;      //!< my solution 1 color for the pipette drawing
  QColor m_sol2_color;      //!< my solution 2 color for the pipette drawing
  QColor m_sol3_color;      //!< my solution 3 color for the pipette drawing
  QColor m_sol4_color;      //!< my solution 4 color for the pipette drawing

  // chart
  QtCharts::QChartView *m_chartView;
  Labonatip_chart *m_labonatip_chart_view;   //!< the main chart is built in a different class

  // zone controls
  double m_ds_perc;          //!< droplet size percentage
  double m_fs_perc;          //!< flow speed percentage
  double m_v_perc;           //!< vacuum percentage

  QString m_version;         //!< software version
  QString m_protocol_path;   //!< protocol path 
  QString m_settings_path;   //!< settings path
  QString m_ext_data_path;   //!< ext data path (save history)
  QTranslator m_translator;
  int m_language_idx;

  // custom strings for translations
  QString m_str_areyousure;
  QString m_str_waiting;
  QString m_str_advanced;
  QString m_str_basic;
  QString m_str_operation_cancelled;
  QString m_str_no_file_loaded;
  QString m_str_information;
  QString m_str_warning;
  QString m_str_error;
  QString m_str_cancel;
  QString m_str_ok;
  QString m_str_PPC1_status_con;
  QString m_str_PPC1_status_discon;
  QString m_str_protocol_running;
  QString m_str_protocol_not_running;
  QString m_str_connect;
  QString m_str_disconnect;
  QString m_str_save_profile;
  QString m_str_load_profile;
  QString m_str_cannot_save_profile;
  QString m_str_cannot_load_profile;
  QString m_str_warning_simulation_only;
  QString m_str_cannot_connect_ppc1;
  QString m_str_cannot_connect_ppc1_twice;
  QString m_str_cannot_connect_ppc1_check_cables; 
  QString m_str_question_find_device;
  QString m_str_ppc1_connected_but_not_running;
  QString m_str_question_stop_ppc1;
  QString m_str_unable_stop_ppc1;
  QString m_str_shutdown_pressed;
  QString m_str_shutdown_pressed_p_off;
  QString m_str_shutdown_pressed_v_off;
  QString m_str_rebooting;
  QString m_str_reconnecting;
  QString m_str_initialization; 
  QString m_str_newtip_msg1;
  QString m_str_newtip_msg2;
  QString m_str_newtip_msg3;
  QString m_str_newtip_msg4;
  QString m_str_newtip_msg5;
  QString m_str_newtip_msg6;
  QString m_str_newtip_msg7;
  QString m_str_newtip_msg8;
  QString m_str_newtip_msg9;
  QString m_str_newtip_msg10;
  QString m_str_standby_operation;
  QString m_str_label_run_protocol;
  QString m_str_label_stop_protocol;
  QString m_str_no_protocol_load_first;
  QString m_str_loaded_protocol_is;
  QString m_str_protocol_confirm;
  QString m_str_progress_msg1;
  QString m_str_progress_msg2;
  QString m_str_ask_msg;
  QString m_str_editor_apply_msg1;
  QString m_str_editor_apply_msg2;
  QString m_str_cleaning_history_msg1;
  QString m_str_cleaning_history_msg2;
  QString m_str_update_time_macro_msg1;
  QString m_str_update_time_macro_msg2;
  QString m_str_pulse_remaining_time;
  QString m_str_pulse_continuous_flowing;
  QString m_str_pulse_waste;
  QString m_str_pulse_full_in;
  QString m_str_operation_cannot_be_done; 
  QString m_str_out_of_bound; 
  QString m_str_user;

  // to visualize the led on the status bar, 
  // I create two different leds and switch between them to create the effect on/off
  QPixmap * led_green;
  QPixmap * led_red;
  QPainter * painter_led_green;
  QPainter * painter_led_red;

  // spacers for the toolbar to create the basic->advanced effect
  QGroupBox * m_g_spacer;
  QAction *m_a_spacer;
};

#endif /* Labonatip_GUI_H_ */
