#pragma once

#include <SFML/Graphics.hpp>
#include <QtCore>
#include <QtGui>

#include <vector>
#include <array>

namespace Zk {
namespace Common {

struct triangleDesc_t
{
	std::array<qint16, 3> vert;
	std::array<QColor, 3> color;
};

QDataStream & operator<<(QDataStream & ds, const triangleDesc_t & td);
QDataStream & operator>>(QDataStream & ds, triangleDesc_t & td);

class LevelLayer
{
public:
	LevelLayer();
	~LevelLayer();
	
	void clear();
	
	void constructMesh(sf::VertexArray & varr) const;
	
	const std::vector<sf::Vertex> & getVertices() const;
	const std::vector<triangleDesc_t> & getTriangleDescriptions() const;
	void setVertices(const std::vector<sf::Vertex> & verts);
	void setTriangleDescriptions(const std::vector<triangleDesc_t> & descs);
	
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
	
	void clear();
	
	const std::vector<LevelLayer*> & getLayers() const;
	const std::vector<QColor> & getPalette() const;
	void setLayers(const std::vector<LevelLayer*> & layers);
	void setPalette(const std::vector<QColor> & colors);
	
	friend QDataStream & operator<<(QDataStream & ds, const Level & l);
	friend QDataStream & operator>>(QDataStream & ds, Level & l);
	
private:
	std::vector<LevelLayer*> layers;
	std::vector<QColor> palette;
	
};

}}
