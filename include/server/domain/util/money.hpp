#ifndef ASCIINEM_SERVER_MONEY_H
#define ASCIINEM_SERVER_MONEY_H

#include <string>
namespace asciinem::server::domain
{

class money
{
public:
    money();
    explicit money( double );
    money( const money& );
    ~money() = default;

    auto operator=( const money& ) -> money&;
    auto operator=( double ) -> money&;
    explicit operator double() const;
    explicit operator int() const;

    void FIX();
    static auto SCALE() -> double
    {
        return 100;
    }

    friend auto operator+( const money&, const money& ) -> money;
    friend auto operator-( const money&, const money& ) -> money;
    friend auto operator*( const money&, double ) -> money;
    friend auto operator*( double, const money& ) -> money;
    friend auto operator/( const money&, const money& ) -> double;

    friend auto operator==( const money&, const money& ) -> bool;
    friend auto operator<( const money&, const money& ) -> bool;

    auto operator+=( const money& ) -> money&;
    auto operator-=( const money& ) -> money&;

    auto operator*=( double ) -> money&;
    auto operator/=( double ) -> money&;

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( m_money_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( m_money_ );
    }

private:
    double m_money_ {};
};

} // namespace asciinem::server::domain
#endif // ASCIINEM_SERVER_MONEY_H

// based on http://www.di-mare.com/adolfo/p/src/money.h
