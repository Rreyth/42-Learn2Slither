#ifndef ROUNDEDRECTANGLESHAPE_HPP
# define ROUNDEDRECTANGLESHAPE_HPP

# include <SFML/Graphics.hpp>
# include <cmath>


class RoundedRectangleShape : public sf::Shape
{
public:
    RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0),
                          float radius = 0);

    void				setSize(const sf::Vector2f& size);
    void				setCornersRadius(float radius);
    void				setCornerPointCount(std::size_t count);
    const sf::Vector2f&	getSize() const;
	float				getCornersRadius() const;
	std::size_t			getCornerPointCount() const;
	std::size_t			getPointCount() const override;
	sf::Vector2f		getPoint(std::size_t index) const override;

private:
    sf::Vector2f	m_size;
    float			m_radius;
    std::size_t		m_cornerPointCount;
};


#endif //ROUNDEDRECTANGLESHAPE_HPP
