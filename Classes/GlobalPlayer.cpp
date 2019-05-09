#include "GlobalPlayer.h"

USING_NS_CC;

GlobalPlayer::GlobalPlayer()
	:Sprite()
{}

GlobalPlayer* GlobalPlayer::createPlayer() {
	GlobalPlayer* globalPlayer = new GlobalPlayer();
	globalPlayer->autorelease();
	return globalPlayer;
}

GlobalPlayer* GlobalPlayer::createPlayer(const std::string& fileName) {
	GlobalPlayer* globalPlayer = new GlobalPlayer();
	globalPlayer->initWithFile(fileName);
	globalPlayer->autorelease();
	return globalPlayer;
}

GlobalPlayer* GlobalPlayer::createPlayerWithSpriteFrameName(const std::string& spriteFrameName) {
	GlobalPlayer* globalPlayer = new GlobalPlayer();
	globalPlayer->initWithSpriteFrameName(spriteFrameName);
	globalPlayer->autorelease();
	return globalPlayer;
}

void GlobalPlayer::initGraphWay(const std::vector< std::vector<std::pair<int, int>> >& gr) {
	_graph = gr;
}

void GlobalPlayer::initStartPostion(int startPosition) {
	_startPosition = startPosition;
}

void GlobalPlayer::initPositionLocation(const std::vector<cocos2d::Vec2>& pos) {
	_positionLocation = pos;
}

void GlobalPlayer::moveTo(int indexLocation) {
	this->_initPath(indexLocation);
}

void GlobalPlayer::update(float dt) {

	if (_path.size() != 0) {
		if (this->getNumberOfRunningActions() == 0) {
			int i = _path.back();
			_path.pop_back();
			_startPosition = i;
			MoveTo* moveTo = MoveTo::create(3.f, _positionLocation[i]);
			this->runAction(moveTo);
		}
	}
}

void GlobalPlayer::_initPath(int indexLocation) {
	const int INF = 10000000;

	//количество вершин
	int n = _graph.size();

	//граф смежности
	//_graph

	//стартовая позиция
	int s = _startPosition;

	//минимальный вес до каждой вершини;?
	std::vector<int> d(n, INF), p(n);

	//вес стартовой позиции всегда равне нулю
	d[s] = 0;
	//посещенные вершины
	std::vector<bool> u(n);

	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j) {
			if (!u[j] && (v == -1 || d[j] < d[v])) {
				v = j;
			}
		}
		if (d[v] == INF) {
			break;
		}
		u[v] = true;

		for (int j = 0; j < _graph[v].size(); ++j) {
			int to = _graph[v][j].first;
			int len = _graph[v][j].second;

			if (d[v] + len < d[to]) {
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}

	_path.clear();
	for (int v = indexLocation; v != s; v = p[v])
		_path.push_back(v);
}