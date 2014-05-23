#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore>

#include <vector>

namespace Zk {
namespace Common {

struct triangleDesc_t
{
	qint16 vert[3];
};

QDataStream & operator<<(QDataStream & ds, const triangleDesc_t & td);
QDataStream & operator>>(QDataStream & ds, triangleDesc_t & td);

class LevelLayer
{
public:
	LevelLayer();
	~LevelLayer();
	
	void constructMesh(sf::VertexArray & varr) const;
	
	void setVertices(const std::vector<sf::Vertex> & verts);
	const std::vector<sf::Vertex> & getVertices() const;
	void setTriangleDescriptions(const std::vector<triangleDesc_t> & descs);
	const std::vector<triangleDesc_t> & getTriangleDescriptions() const;
	
	void calculateTexCoords();
	
	friend QDataStream & operator<<(QDataStream & ds, const LevelLayer & ll);
	friend QDataStream & operator>>(QDataStream & ds, LevelLayer & ll);
	
private:
	std::vector<sf::Vertex> verts;
	std::vector<triangleDesc_t> descs;
	
};

class Level
{
public:
	Level();
	~Level();
	
	std::vector<LevelLayer*> & getLayers();
	
	friend QDataStream & operator<<(QDataStream & ds, const Level & l);
	friend QDataStream & operator>>(QDataStream & ds, Level & l);
	
private:
	std::vector<LevelLayer*> layers;
	
};

}}