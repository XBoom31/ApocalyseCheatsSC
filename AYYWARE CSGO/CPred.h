#pragma once
#include "stdafx.h"
#define MAX_SPLITSCREEN_PLAYERS 1

class IMoveHelper;
class CBaseHandle;
class CMoveData
{
public:
	bool			m_bFirstRunOfFunctions : 1;
	bool			m_bGameCodeMovedPlayer : 1;
	bool			m_bNoAirControl : 1;

	HANDLE      	m_nPlayerHandle;	// edict index on server, client entity handle on client

	int				m_nImpulseCommand;	// Impulse command issued.
	Vector			m_vecViewAngles;	// Command view angles (local space)
	Vector			m_vecAbsViewAngles;	// Command view angles (world space)
	int				m_nButtons;			// Attack buttons.
	int				m_nOldButtons;		// From host_client->oldbuttons;
	float			m_flForwardMove;
	float			m_flSideMove;
	float			m_flUpMove;

	float			m_flMaxSpeed;
	float			m_flClientMaxSpeed;

	// Variables from the player edict (sv_player) or entvars on the client.
	// These are copied in here before calling and copied out after calling.
	Vector			m_vecVelocity;		// edict::velocity		// Current movement direction.
	Vector			m_vecAngles;		// edict::angles
	Vector			m_vecOldAngles;

	// Output only
	float			m_outStepHeight;	// how much you climbed this move
	Vector			m_outWishVel;		// This is where you tried 
	Vector			m_outJumpVel;		// This is your jump velocity

										// Movement constraints	(radius 0 means no constraint)
	Vector			m_vecConstraintCenter;
	float			m_flConstraintRadius;
	float			m_flConstraintWidth;
	float			m_flConstraintSpeedFactor;
	bool			m_bConstraintPastRadius;		///< If no, do no constraining past Radius.  If yes, cap them to SpeedFactor past radius

	void			SetAbsOrigin(const Vector &vec);
	const Vector	&GetAbsOrigin() const;

private:
	Vector			m_vecAbsOrigin;		// edict::origin
};



class CPrediction
{
	// Construction
public:

	virtual			~CPrediction(void) = 0;//

	virtual void	Init(void) = 0;//
	virtual void	Shutdown(void) = 0;//

									   // Implement IPrediction
public:

	virtual void	Update
		(
			int startframe,		// World update ( un-modded ) most recently received
			bool validframe,		// Is frame data valid
			int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
			int outgoing_command	// Last command (most recent) sent to server (un-modded)
			);//

	virtual void	PreEntityPacketReceived(int commands_acknowledged, int current_world_update_packet);//
	virtual void	PostEntityPacketReceived(void);//5
	virtual void	PostNetworkDataReceived(int commands_acknowledged);//

	virtual void	OnReceivedUncompressedPacket(void);//

													   // The engine needs to be able to access a few predicted values
	virtual void	GetViewOrigin(Vector& org);//
	virtual void	SetViewOrigin(Vector& org);//
	virtual void	GetViewAngles(Vector& ang);//10
	virtual void	SetViewAngles(Vector& ang);//

	virtual void	GetLocalViewAngles(Vector& ang);//
	virtual void	SetLocalViewAngles(Vector& ang);//

	virtual bool	InPrediction(void) const;//14
	virtual bool	IsFirstTimePredicted(void) const;//

	virtual int		GetLastAcknowledgedCommandNumber(void) const;//

#if !defined( NO_ENTITY_PREDICTION )
	virtual int		GetIncomingPacketNumber(void) const;//
#endif

														/*float			GetIdealPitch( int nSlot ) const
														{
														if ( nSlot == -1 )
														{
														Assert( 0 );
														return 0.0f;
														}
														return m_Split[ nSlot ].m_flIdealPitch;
														}*/

	virtual void	CheckMovingGround(CBaseEntity *player, double frametime);//
	virtual void	RunCommand(CBaseEntity *player, CInput::CUserCmd *ucmd, IMoveHelper *moveHelper);//

	virtual void	SetupMove(CBaseEntity *player, CInput::CUserCmd *ucmd, IMoveHelper *pHelper, CMoveData *move);//20
	virtual void	FinishMove(CBaseEntity *player, CInput::CUserCmd *ucmd, CMoveData *move);//
	virtual void	SetIdealPitch(int nSlot, CBaseEntity *player, const Vector& origin, const Vector& angles, const Vector& viewheight);//

	virtual void	CheckError(int nSlot, CBaseEntity *player, int commands_acknowledged);//

																						  // Called before and after any movement processing
																						  /*void			StartCommand( C_BasePlayer *player, CUserCmd *cmd );
																						  void			FinishCommand( C_BasePlayer *player );

																						  // Helpers to call pre and post think for player, and to call think if a think function is set
																						  void			RunPreThink( C_BasePlayer *player );
																						  void			RunThink (C_BasePlayer *ent, double frametime );
																						  void			RunPostThink( C_BasePlayer *player );*/

public:
	virtual void	_Update
		(
			int nSlot,
			bool received_new_world_update,
			bool validframe,		// Is frame data valid
			int incoming_acknowledged, // Last command acknowledged to have been run by server (un-modded)
			int outgoing_command	// Last command (most recent) sent to server (un-modded)
			);

	// Actually does the prediction work, returns false if an error occurred
	bool			PerformPrediction(int nSlot, CBaseEntity *localPlayer, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

	void			ShiftIntermediateDataForward(int nSlot, int slots_to_remove, int previous_last_slot);
	void			RestoreEntityToPredictedFrame(int nSlot, int predicted_frame);
	int				ComputeFirstCommandToExecute(int nSlot, bool received_new_world_update, int incoming_acknowledged, int outgoing_command);

	void			DumpEntity(CBaseEntity *ent, int commands_acknowledged);

	void			ShutdownPredictables(void);
	void			ReinitPredictables(void);

	void			RemoveStalePredictedEntities(int nSlot, int last_command_packet);
	void			RestoreOriginalEntityState(int nSlot);
	void			RunSimulation(int current_command, float curtime, CInput::CUserCmd *cmd, CBaseEntity *localPlayer);
	void			Untouch(int nSlot);
	void			StorePredictionResults(int nSlot, int predicted_frame);
	bool			ShouldDumpEntity(CBaseEntity *ent);

	void			SmoothViewOnMovingPlatform(CBaseEntity *pPlayer, Vector& offset);
	void			ResetSimulationTick();
	void			ShowPredictionListEntry(int listRow, int showlist, CBaseEntity *ent, int &totalsize, int &totalsize_intermediate);
	void			FinishPredictionList(int listRow, int showlist, int totalsize, int totalsize_intermediate);
	void			CheckPredictConvar();

#if !defined( NO_ENTITY_PREDICTION )

#endif

};
