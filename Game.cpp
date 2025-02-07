#include "Game.h"
#include <iostream>
#include "Logger.h"
#include "states/GameState.h"
bool game::Init()
{
	try
	{
		m_pConsole = std::make_unique<Console>();
	}
	catch(std::exception& e)
	{
		std::string error = e.what();
		TRPG_ERROR(error);
		return false;
	}
	//m_pConsole = std::make_unique<Console>();
	m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
	m_pKeyboard = std::make_unique<Keyboard>();
	m_pStateMachine = std::make_unique<StateMachine>();

	m_pStateMachine->PushState(std::make_unique<GameState>(*m_pConsole,*m_pKeyboard,*m_pStateMachine));

	return true;
}

void game::ProcessInputs()
{
	if (m_pKeyboard->IsKeyJustPressed(KEY_ESCAPE))
		m_bIsRunning = false;

	//if (!m_pStateMachine->GetCurrentState())
	if(m_pStateMachine->Empty())
	{
		TRPG_ERROR("NO STATES IN STATE MACHINE TO PROCESS INPUTS");
		m_bIsRunning = false;
		return;
	}
		m_pStateMachine->GetCurrentState()->ProcessInputs();
	//std::cout << "Process Inputs\n";
	//TRPG_LOG("Process Inputs");
}

void game::ProcessEvents()
{
	// Get the number of Console Inputs 
	if (!GetNumberOfConsoleInputEvents(m_hConsoleIn, &m_NumRead))
	{
		DWORD error = GetLastError();
		TRPG_ERROR("Failed to get number of console input events" + error);
		return;
	}
	if (m_NumRead <= 0)
		return;

	if (!PeekConsoleInput(m_hConsoleIn, m_InRecBuf, 128, &m_NumRead))
	{
		DWORD error = GetLastError();
		TRPG_ERROR("Failed to peek events" + error);
		return;
	}
	for (int i = 0; i < m_NumRead; i++)
	{
		switch (m_InRecBuf[i].EventType)
		{
		case KEY_EVENT:
			//To do list: Create a function to process key events
			KeyEventProcess(m_InRecBuf[i].Event.KeyEvent);
			break;
		default:
			break;
		}
	}
	//clear of flush other inputs events
	FlushConsoleInputBuffer(m_hConsoleIn);
}

void game::Update()
{
	//if (!m_pStateMachine->GetCurrentState())
	if(m_pStateMachine->Empty())
	{
		TRPG_ERROR("NO STATES IN STATE MACHINE TO UPDATE");
		m_bIsRunning = false;
		return;
	}
	m_pStateMachine->GetCurrentState()->Update();

	m_pKeyboard->Update();
	//std::cout << "Update\n";
	//TRPG_ERROR("Update");
}

void game::Draw()
{
	//std::cout << "Draw\n";
	//TRPG_LOG("Draw");
	//if (!m_pStateMachine->GetCurrentState())
	if(m_pStateMachine->Empty())
	{
		TRPG_ERROR("NO STATES IN STATE MACHINE TO DRAW");
		m_bIsRunning = false;
		return;
	}
	m_pStateMachine->GetCurrentState()->Draw();

	m_pConsole->Write(10,10,L"Paladins of Krovos",RED);
	m_pConsole->Draw();
}

void game::KeyEventProcess(KEY_EVENT_RECORD keyEvent)
{
	if (keyEvent.bKeyDown)
	{
		m_pKeyboard->OnKeyDown(keyEvent.wVirtualKeyCode);
		//To do: keyboard class in here
		//std::cout << "key pressed!" << keyEvent.wVirtualKeyCode << std::endl;
	}
	else
	{
		m_pKeyboard->OnKeyUp(keyEvent.wVirtualKeyCode);
		//std::cout << "key released" << keyEvent.wVirtualKeyCode << std::endl;
	}
}

game::game()
	 :m_bIsRunning(true)
	, m_pConsole{nullptr}
	, m_pKeyboard{nullptr}
	, m_pStateMachine{nullptr}
{

}

game::~game()
{

}

void game::Run()
{
	if (!Init())
		m_bIsRunning = false;
			
	while (m_bIsRunning)
	{	
		ProcessEvents();
		ProcessInputs();
		Update();
		Draw();
	}
	std::cout << "piss off\n";
}
