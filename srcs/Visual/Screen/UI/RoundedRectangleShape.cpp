#include <Visual/Screen/UI/RoundedRectangleShape.hpp>

RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f &size, float radius)
: m_size(size)
, m_radius(radius)
, m_cornerPointCount(std::max<std::size_t>(2, static_cast<std::size_t>(std::ceil(M_PI * radius / 2.f))))
{
	update();
}


void	RoundedRectangleShape::setSize(const sf::Vector2f &size)
{
	m_size = size;
	update();
}


void	RoundedRectangleShape::setCornersRadius(float radius)
{
	m_radius = radius;
	update();
}


void	RoundedRectangleShape::setCornerPointCount(std::size_t count)
{
	m_cornerPointCount = std::max<std::size_t>(count, 2);;
	update();
}


const sf::Vector2f	&RoundedRectangleShape::getSize() const
{
	return m_size;
}


float RoundedRectangleShape::getCornersRadius() const
{
	return m_radius;
}


std::size_t	RoundedRectangleShape::getCornerPointCount() const
{
	return m_cornerPointCount;
}

std::size_t RoundedRectangleShape::getPointCount() const
{
	return m_cornerPointCount * 4;
}


sf::Vector2f	RoundedRectangleShape::getPoint(std::size_t index) const
{
	std::size_t corner = index / m_cornerPointCount;
	std::size_t idxInCorner = index % m_cornerPointCount;
	float deltaAngle = 90.f / (m_cornerPointCount - 1);
	float startAngle = 0.f;
	sf::Vector2f center;

	switch (corner)
	{
		case 0: // top-left
			startAngle = 180.f;
			center = { m_radius, m_radius };
			break;
		case 1: // top-right
			startAngle = 270.f;
			center = { m_size.x - m_radius, m_radius };
			break;
		case 2: // bottom-right
			startAngle =   0.f;
			center = { m_size.x - m_radius, m_size.y - m_radius };
			break;
		case 3: // bottom-left
			startAngle =  90.f;
			center = { m_radius, m_size.y - m_radius };
			break;
	}

	float angle = startAngle + idxInCorner * deltaAngle;
	float rad = angle * 3.141592654f / 180.f;
	return { std::cos(rad) * m_radius + center.x,
			 std::sin(rad) * m_radius + center.y };
}
