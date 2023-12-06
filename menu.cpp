#include "menu.hpp"

Menu::Menu() {
    window = new sf::RenderWindow();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();
    cred = new sf::Texture();

    set_values();
}

Menu::~Menu() {
    delete window;
    delete font;
    delete image;
    delete cred;
    delete bg;
}

void Menu::set_values() {
    window->create(sf::VideoMode(1920, 1061), "Menu SFML");
    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("./arial.ttf");
    image->loadFromFile("./Baldur's Gate 3.png");
    cred->loadFromFile("./cred.png");

    bg->setTexture(*image);

    options = { "Banqi", "Play", "Credits", "Quit" };
    texts.resize(4);
    coords = { {800,30},{720,191},{700,282},{690,370}};
    sizes = { 50,40,35,35 };

    for (int i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Red);
        texts[i].setPosition(coords[i]);
    }
    texts[1].setOutlineThickness(7);
    pos = 1;
    val = 0;
}

void Menu::loop_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
            if (pos < 3) {
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(7);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
                bg->setTexture(*image);
                draw_all();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
            if (pos > 1) {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(7);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
                bg->setTexture(*image);
                draw_all();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
            theselect = true;
            if (pos == 1)
            {
                val = 1;
                window->close();
            }
            if (pos == 3) {
                window->close();
            }
            if (pos == 2) {
                window->clear();
                bg->setTexture(*cred);
                window->draw(*bg);
                window->display();
            }
            std::cout << options[pos] << '\n';
        }

    }
}

void Menu::run_menu() {
    draw_all();
    while (window->isOpen()) {
        loop_events();
    }
}

void Menu::draw_all() {
    window->clear();
    window->draw(*bg);
    for (auto t : texts) {
        window->draw(t);
    }

    window->display();
}

