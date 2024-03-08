#include <iostream>
#include <array>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>

#include <Helper.h>

//////////////////////////////////////////////////////////////////////
/// NOTE: this include is needed for environment-specific fixes     //
/// You can remove this include and the call from main              //
/// if you have tested on all environments, and it works without it //
#include "env_fixes.h"                                              //
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/// This class is used to test that the memory leak checks work as expected even when using a GUI
class SomeClass {
public:
    explicit SomeClass(int) {}
};

SomeClass* getC() {
    return new SomeClass{ 2 };
}
//////////////////////////////////////////////////////////////////////


class Planet
{
private:
    std::string m_name;
    sf::CircleShape m_shape;
public:
    Planet(const std::string& name, const sf::Vector2f& position, const float& radius) :
        m_name(name),
        m_shape(radius)
    {
        m_shape.setOrigin(sf::Vector2f(1, 1) * radius);
        m_shape.setPosition(position);
    }

    Planet(const Planet& other) :
        m_name(other.m_name),
        m_shape(other.m_shape)
    {

    }

    Planet operator = (const Planet& other)
    {
        if (this != &other)
        {
            this->m_name = other.m_name;
            this->m_shape = other.m_shape;
        }
        return *this;
    }

    ~Planet()
    {

    }

    void display(sf::RenderWindow& renderWindow)
    {
        renderWindow.draw(m_shape);
    }

    friend std::ostream& operator << (std::ostream& os, const Planet& planet)
    {
        os << "(name = " << planet.m_name << ")";
        return os;
    }
};

void GO()
{
    Planet dune{ "Dune", sf::Vector2f(0.4f, 0.6f), 0.2f };
    sf::RenderWindow window(sf::VideoMode(900, 900), "Muad'dib");
    sf::View view;
    view.setSize(sf::Vector2f(1, 1));
    view.setCenter(sf::Vector2f(0.5, 0.5));
    window.setView(view);
    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float dt = frameClock.restart().asSeconds();

        std::cout << "fps = " << 1 / dt << std::endl;

        window.clear();
        dune.display(window);
        window.display();

    }
    exit(0);
}

int main()
{
    GO();

    exit(0);
    //exit(0);
    ////////////////////////////////////////////////////////////////////////
    /// NOTE: this function call is needed for environment-specific fixes //
    init_threads();                                                       //
    ////////////////////////////////////////////////////////////////////////
    ///
    //std::cout << "Hello, world!\n";
    //std::array<int, 100> v{};
    //int nr;
    //std::cout << "Introduceți nr: ";
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    //std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    //for(int i = 0; i < nr; ++i) {
    //    std::cout << "v[" << i << "] = ";
    //    std::cin >> v[i];
    //}
    //std::cout << "\n\n";
    //std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    //for(int i = 0; i < nr; ++i) {
    //    std::cout << "- " << v[i] << "\n";
    //}
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu de utilizare cod generat                     ///
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////

    SomeClass* c = getC();
    std::cout << c << "\n";
    delete c;

    sf::RenderWindow window;
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: sync with env variable APP_WINDOW from .github/workflows/cmake.yml:31
    window.create(sf::VideoMode({ 800, 700 }), "My Window", sf::Style::Default);
    ///////////////////////////////////////////////////////////////////////////
    //
    ///////////////////////////////////////////////////////////////////////////
    /// NOTE: mandatory use one of vsync or FPS limit (not both)            ///
    /// This is needed so we do not burn the GPU                            ///
    window.setVerticalSyncEnabled(true);                            ///
    /// window.setFramerateLimit(60);                                       ///
    ///////////////////////////////////////////////////////////////////////////

    //exit(0);
    while (window.isOpen()) {
        bool shouldExit = false;
        sf::Event e{};
        while (window.pollEvent(e)) {
            switch (e.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << "New width: " << window.getSize().x << '\n'
                    << "New height: " << window.getSize().y << '\n';
                break;
            case sf::Event::KeyPressed:
                std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
                if (e.key.code == sf::Keyboard::Escape)
                    shouldExit = true;
                break;
            default:
                break;
            }
        }
        if (shouldExit) {
            window.close();
            break;
        }
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);

        window.clear();
        window.display();
    }
    return 0;
}
