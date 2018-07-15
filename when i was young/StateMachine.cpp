#include <string>
#include <unordered_map>
#include <unistd.h>

using namespace std;

typedef int g_state;
g_state NULL_STATE = -1;

class FSM;

class State
{
public :
	virtual void OnStateEnter() = 0;
	virtual void OnStateTimeTick(int time) = 0;
	virtual void OnStateExit() = 0;
	
protected:
	FSM * fsm = nullptr;
};

class FSM
{
public:
	void InitState(g_state stateNo)
	{
		_cur_state = stateNo;
	}

	bool Registe(g_state stateNo, State * state)
	{
		auto resIt = _all_state.insert(make_pair(stateNo, state));
		return resIt.first;
	}

	bool Trans(g_state nextStateNo)
	{
		auto curStateIt = _all_state.find(_cur_state);
		if (curStateIt == nullptr)
		{
			return false;
		}

		auto nextStateIt = _all_state.find(nextStateNo);
		if (nextStateIt == nullptr)
		{
			return false;
		}

		curStateIt->second->OnStateExit();
		nextStateIt->second->OnStateEnter();

		_cur_state = nextStateIt->first;
		return true;
	}

	void Tick(int time)
	{
		auto curStateIt = _all_state.find(_cur_state);
		if (curStateIt == nullptr)
		{
			//log
			return;
		}

		curStateIt->second->OnStateTimeTick(time);
	}

private:
	unordered_map<g_state, State*> _all_state;
	g_state _cur_state;
};


// ==================Test Code======================
const g_state STATE_START_TRUN = 1;
const g_state STATE_ON_TURN = 2;
const g_state STATE_END_TURN = 3;

class StateStartTrun : public State
{
public:
	StateStartTurn(FSM * fsm, int timeId) : State(fsm), _time_id(timeId) {}

	void OnStateEnter() override
	{
		cout << "enter start turn" << endl;
	}

	void OnStateExit() override
	{
		cout << "exit start turn" << endl;
	}

	void OnStateTimeTick(int time) override
	{
		if (time == _time_id)
		{
			cout << " on start turn time tick" << endl;
			fsm->Trans(STATE_ON_TURN);
		}
	}

private:
	int _time_id;
};

class StateOnTrun : public State
{
public:
	StateOnTurn(FSM * fsm, int timeId) : State(fsm), _time_id(timeId) {}

	void OnStateEnter() override
	{
		cout << "enter on turn" << endl;
	}

	void OnStateExit() override
	{
		cout << "exit on turn" << endl;
	}

	void OnStateTimeTick(int time) override
	{
		if (time == _time_id)
		{
			cout << " on start turn time tick" << endl;
			fsm->Trans(STATE_END_TRUN);
		}
	}

private:
	int _time_id;
};

class StateEndTrun : public State
{
public:
	StateEndTurn(FSM * fsm) : State(fsm) {}

	void OnStateEnter() override
	{
		cout << "enter end turn" << endl;
	}

	void OnStateExit() override
	{
		cout << "exit end turn" << endl;
	}

	void OnStateTimeTick() override
	{
			cout << " on end turn time tick" << endl;
	}

};

int main()
{
	FSM fsm = new FSM();
	State * stateStartTurn = new StateStartTrun(fsm, 5);
	State * stateOnTurn = new StateOnTrun(fsm, 10);
	State * stateEndTurn = new StateEndTrun(fsm);

	fsm->Registe(STATE_START_TRUN,stateStartTurn);
	fsm->Registe(STATE_ON_TRUN, stateOnTurn);
	fsm->Registe(STATE_END_TRUN, stateEndTurn);

	fsm->InitState(STATE_START_TRUN);

	int time = 0
	while (true)
	{
		++time;
		fsm->Tick(time);
	}

	return 0;
}