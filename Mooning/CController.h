#ifndef CCONTROLLER_H
#define CCONTROLLER_H
/*! \file CController.h
*
*  \author Mat Buckland 2002
*
*	\brief Controller class for the lunar lander project.
*/

#include <windows.h>
#include <vector>
#include <mmsystem.h>

#include "utils.h"
#include "CLander.h"
#include "CgaLander.h"

using namespace std;

/// Class declaration
class CController 
{
private:

	//pointer to the genetic algorithm
	CgaLander* m_pGA;

	vector<CLander> m_vecLanders;

	//stores all out genomes
	vector<SGenome> m_vecPop;

	//toggles the speed at which the simulation runs
	bool m_bFastRender;

	//if switched on shows best attempt each generation
	bool m_bShowFittest;

  //true if we have successfully landed
  bool            m_bSuccess;

  //vertex buffer for the stars
  vector<SPoint>  m_vecStarVB;

  //vertex buffer to store the landing pads vertices
  vector<SPoint>  m_vecPadVB;

  //position of the landing pad
  SVector2D       m_vPadPos;

  //generation counter
  int m_iGeneration;

  //keeps a track of the fittest lander each generation
  int m_iFittest;

  //keeps a record of the window size
  int             m_cxClient,
                  m_cyClient;

  void WorldTransform(vector<SPoint> &pad);

  void RenderLandingPad(HDC &surface);

  void Success();


public:
  
  CController(int cxClient, int cyClient);

  ~CController()
  {
	  if(m_pGA)
		  delete m_pGA;
  }

  //this is called from the windows message loop and calls
  //CLander::CheckForKeyPress() which tests for user input 
  //and updates the lander's position accordingly
  bool  Update(double TimeElapsed);

  //initialize a new run
  void  NewRun();

  //this is called from WM_PAINT to render all the objects
  //in our scene
  void  Render(HDC &surface);

  void ToggleFastRender() {m_bFastRender = !m_bFastRender;}

  void ToggleShowFittest();

  ///accesor method
  bool FastRender()const {return m_bFastRender;}
  bool ShowFittest()const {return m_bShowFittest;}
  
};


#endif