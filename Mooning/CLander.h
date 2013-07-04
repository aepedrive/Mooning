#ifndef CLANDER_H
#define CLANDER_H

#include "windows.h"
#include <vector>

#include "utils.h"
#include "defines.h"
#include "CTimer.h"
#include "SVector2D.h"
#include "C2DMatrix.h"

using namespace std;
/*! \file CLander.h
	\brief Header file. struct SGene and class CLander definitions.
*/

//! Enumerate a type for each different action the Lander can perform
/*! Defines actions taken by spaceship */
enum action_type{rotate_left, /*!< Rotate counterclockwise */
				 rotate_right,/*!< Rotate clockwise */
				 thrust,	  /*!< Apply rocket thrust */
				 non/*!< Do nothing */};

//-------------------------------------------------------------------
struct SGene
{
	action_type action;
	
	int duration; /*!< duration the action is applied measured in ticks */

	SGene()
	{
		/*! \brief
		* Creates a random action of a random duration
		*/
		action = (action_type)RandInt(0, 3);
		duration = RandInt(1, MAX_ACTION_DURATION);
	}

	SGene(action_type a , int d):action(a), duration(d) {}

	//need to overload the == operator so we can test if actions are 
	//equal (used in the crossover process of the GA)
	bool operator==(const SGene &rhs) const
	{
		return (action == rhs.action) && (duration == rhs.duration);
	}
};

//-------------------------------------------------------------------

class CLander
{
private:
		
	SVector2D		m_vStartPos; /*!< keep a record of the start position */
	
	double			m_dStartRotation; /*!< keep a record of the start rotation */
	
	int         m_iPadX; /*!< this will hold the horizontal position of the landing pad */
	
	vector<action_type> m_vecActions; /*!< This will hold a series of actions decoded from the ships chromosomes */
	
		
	int         m_cTick; /*!< The action counter. Tells us which is the current action. */
	//its fitness score
	double			m_dFitness;

	void CalculateFitness();
	
	//position in world
	SVector2D		        m_vPos;
	
  //rotation in the world
	double			        m_dRotation;

	//scaling factor for rendering ship
  double			        m_dScale;
	
	//ships mass
  double			        m_dMass;

  //and velocity
  SVector2D		        m_vVelocity;
        
  //need to know where landing pad is for collision detection
  SVector2D           m_vPadPos;
	
	//buffer to store the ships vertices
  vector<SPoint>      m_vecShipVB;

  //buffer to hold our transformed vertices
  vector<SPoint>      m_vecShipVBTrans;

  //and the jets vertices
  vector<SPoint>      m_vecJetVB;
  vector<SPoint>      m_vecJetVBTrans;

  //we use this to determine whether to render the ships jet or not
  //(if the user is pressing thrust then the jet is rendered)
  bool                m_bJetOn;

  //local copy of client window size
	int				          m_cxClient;
	int				          m_cyClient;

  //used to flag whether or not we have already tested for success
  //or failure
  bool                m_bCheckedIfLanded;


	//returns true if the user has satisfied all the conditions for landing
  bool    LandedOK();

	//tests if any vertex of the ship is below the level of the landing
  //platform
  bool	  TestForImpact(vector<SPoint> &ship);

  //this function transforms the ships vertices so we can display them
  void WorldTransform(vector<SPoint> &ship);



public:

	CLander(int cxClient,	/*!< [in] Local record of Window's x position*/
          int cyClient,		/*!< [in] Local record of Window's y position*/
          double rot,		/*!< [in] Starting rotation of lander */
          SVector2D pos,    /*!< [in] Starting position of lander */
          SVector2D pad /*!< [in] Landing pad position */);
  
	void Render(HDC &surface); /*!< Renders ship */
  
	void Reset(SVector2D &NewPadPos); /*!< Resets all relevant variables for the start of a new attempt */	

	bool UpdateShip(); /*!< Another implemetation of UpdateShip. Will know its function
						later on 2103-07-03. */
	void Decode(const vector<SGene> &actions); /*!< Will know its function later on. 2013-07-03. */

	/// Accesor method
	SVector2D Pos()const {return m_vPos;}
	/// Accesor method
	vector<action_type> GetActionVector() const {return m_vecActions;}
	/// Accesor method
	double Fitness() const {return m_dFitness;}

};

#endif