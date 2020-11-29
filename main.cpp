#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>
#include <stack>
#include <iostream>

// system settings
const int WIDTH = 1600, HEIGHT = 900;
const double PI = acos(-1);
const int step = 3;

class LSystem {
private:
    std::string axiom;
    char chr1, chr2;
    std::string rule1, rule2;
    int angle, gens;
public:
    LSystem(std::string _axiom, char _chr1, char _chr2, std::string _rule1, std::string _rule2,
             int _angle, int _gens) {
        axiom = _axiom;
        chr1 = _chr1;
        chr2 = _chr2;
        rule1 = _rule1;
        rule2 = _rule2;
        angle = _angle;
        gens = _gens;

        generate();
    }

    LSystem(std::string _axiom, char _chr1, std::string _rule1, int _angle, int _gensNumber) {
        axiom = _axiom;
        chr1 = _chr1;
        chr2 = '#';
        rule1 = _rule1;
        rule2 = "";
        angle = _angle;
        gens = _gensNumber;

        generate();
    }

    void applyRules() {
        std::string res;
        for (char c : axiom) {
            if (c == chr1)
                res += rule1;
            else if (c == chr2)
                res += rule2;
            else
                res += c;
        }

        axiom = res;
    }

    void inverseAxiom() {
        for (char &c : axiom) {
            if (c == '-')
                c = '+';
            else if (c == '+')
                c = '-';
        }
    }

    void generate() {
        for (int gen = 1; gen <= gens; ++gen) {
            applyRules();
        }

        if (gens % 2 == 0) {
            inverseAxiom();
        }
    }

    [[nodiscard]] std::string getAxiom() const { return axiom; }
    [[nodiscard]] int getGens() const { return gens; }
    [[nodiscard]] char getChr1() const { return chr1; }
    [[nodiscard]] char getChr2() const { return chr2; }
    [[nodiscard]] int getAngle() const { return angle; }
};

struct RobotData {
    double x, y;
    double angle; // in degrees
};

class Robot {
private:
    std::string name;
    double beginX, beginY;
    double endX, endY;
    double angle; // in degrees

    std::stack<RobotData> *memory;

    void updateEndCoords() {
        double angle_rad = angle * 2 * PI / 360;
        endX = beginX + 1 * cos(angle_rad);
        endY = beginY - 1 * sin(angle_rad);
    }
public:
    Robot(std::string _name, double _beginX, double _beginY, double _endX, double _endY) {
        name = _name;
        beginX = _beginX;
        endX = _endX;
        beginY = _beginY;
        endY = _endY;
        angle = 0;

        memory = new std::stack<RobotData>();
    }

    void move() {
        double angle_rad = angle * 2 * PI / 360;
        double dx = step * cos(angle_rad);
        double dy = step * sin(angle_rad);
        beginX = beginX + dx;
        beginY = beginY - dy;
        updateEndCoords();
    }

    void rotate(int phi) {
        angle += phi;
        updateEndCoords();
    }

    void setBeginX(double new_begin_x) {
        beginX = new_begin_x;
        updateEndCoords();
    }

    void setBeginY(double new_begin_y) {
        beginY = new_begin_y;
        updateEndCoords();
    }

    void setAngle(double new_angle) {
        angle = new_angle;
        updateEndCoords();
    }

    [[nodiscard]] double getBeginX() const { return beginX; }
    [[nodiscard]] double getEndX() const { return endX; }
    [[nodiscard]] double getBeginY() const { return beginY; }
    [[nodiscard]] double getEndY() const { return endY; }
    [[nodiscard]] double getAngle() const { return angle; }
    [[nodiscard]] std::string getName() const { return name; }
    [[nodiscard]] std::stack<RobotData>* getMemory() const { return memory; }
};

class TextButton {
private:
    sf::Text* textButton;
    std::string text;
    sf::Font font;
    float x, y;
    int width, height;
    bool isFocus;

    void setFont() { font.loadFromFile("./fonts/arial.ttf"); }
public:
    TextButton(const std::string& _text, sf::Color color, int characterSize, float _x, float _y, int _width, int _height) {
        setFont();

        text = _text;
        textButton = new sf::Text(_text, font, characterSize);
        textButton->setColor(color);
        textButton->setPosition(_x, _y);
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        isFocus = false;
    }

    TextButton(const std::string& _text, float _x, float _y, float _width, float _height) {
        setFont();

        text = _text;
        textButton = new sf::Text(_text, font, 20);
        textButton->setColor(sf::Color::Black);
        textButton->setPosition(_x, _y);
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        isFocus = false;
    }

    void setColor(sf::Color color) { textButton->setColor(color); }
    void setFocus() { isFocus = true; }
    void setUnfocus() { isFocus = false; }

    bool haveFocus() const { return isFocus; }

    sf::Text getSFMLText() const { return *textButton; }
    std::string getText() const { return textButton->getString(); }
    sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }

    bool contains(sf::Vector2i mousePosition) const {
        int mouseX = mousePosition.x, mouseY = mousePosition.y;
        return (mouseX >= x and mouseX <= (x + width) and mouseY >= y and mouseY <= (y + height));
    }
    void changeColorOnHover() {
        if (haveFocus()) {
            textButton->setColor(sf::Color::Blue);
        } else {
            textButton->setColor(sf::Color::Black);
        }
    }

    void changeFocusOnHover(sf::Vector2i mousePosition) {
        if (contains(mousePosition)) {
            setFocus();
        } else {
            setUnfocus();
        }
    }

    void setPosition(const sf::Vector2f& newPosition) {
        x = newPosition.x;
        y = newPosition.y;

        textButton = new sf::Text(text, font, 20);
        textButton->setColor(sf::Color::Black);
        textButton->setPosition(newPosition.x, newPosition.y);
    }
};

class TextField {
private:
    sf::Text* textField;
    std::string text;
    sf::Font font;
    float x, y;
    int width, height;
    bool isFocus;

    void setFont() { font.loadFromFile("./fonts/arial.ttf"); }
public:
    TextField(const std::string& _text, sf::Color color, int characterSize, float _x, float _y, int _width, int _height) {
        setFont();

        text = _text;
        textField = new sf::Text(_text, font, characterSize);
        textField->setColor(color);
        textField->setPosition(_x, _y);
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        isFocus = false;
    }

    TextField(const std::string& _text, float _x, float _y, int _width, int _height) {
        setFont();

        text = _text;
        textField = new sf::Text(_text, font, 20);
        textField->setColor(sf::Color::Black);
        textField->setPosition(_x, _y);
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        isFocus = false;
    }

    TextField(const std::string& _text, int _width, int _height) {
        setFont();

        text = _text;
        textField = new sf::Text(_text, font, 20);
        textField->setColor(sf::Color::Black);
        textField->setPosition(0, 0);
        x = 0;
        y = 0;
        width = _width;
        height = _height;
        isFocus = false;
    }

    TextField(float _x, float _y, int _width, int _height) {
        setFont();

        text = "";
        textField = new sf::Text("", font, 20);
        textField->setColor(sf::Color::Black);
        textField->setPosition(0, 0);
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        isFocus = false;
    }

    void setColor(sf::Color color) { textField->setColor(color); }
    void setFocus() { isFocus = true; }
    void setUnfocus() { isFocus = false; }

    bool haveFocus() const { return isFocus; }

    sf::Text getSFMLText() const { return *textField; }
    std::string getText() const { return textField->getString(); }
    sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }

    size_t getTextSize() const { return text.size(); }

    bool contains(const sf::Vector2i& mousePosition) {
        float mouseX = mousePosition.x, mouseY = mousePosition.y;
        return (mouseX >= x and mouseX <= (x + width) and mouseY >= y and mouseY <= (y + height));
    }

    void changeColorOnHover() {
        if (haveFocus()) {
            textField->setColor(sf::Color::Blue);
        } else {
            textField->setColor(sf::Color::Black);
        }
    }

    void changeFocusOnHover(const sf::Vector2i& mousePosition) {
        if (contains(mousePosition)) {
            setFocus();
        } else {
            setUnfocus();
        }
    }

    void setPosition(const sf::Vector2f& newPosition) {
        x = newPosition.x;
        y = newPosition.y;

        delete textField;

        textField = new sf::Text(text, font, 20);
        textField->setColor(sf::Color::Black);
        textField->setPosition(newPosition.x, newPosition.y);
    }

    void updateSFMLText() {
        textField = new sf::Text(text, font, 20);
        textField->setColor(sf::Color::Black);
        textField->setPosition(x, y);
    }

    void addCharacter(char c) {
        text += c;
        updateSFMLText();
    }

    void deleteLastCharacter() {
        if (int(text.size()) < 1)
            return;
        text = text.substr(0, text.size() - 1);
        updateSFMLText();
    }

    void setText(const std::string& newText) {
        text = newText;
        updateSFMLText();
    }

    void addText(const std::string& newText) {
        text += newText;
        updateSFMLText();
    }

    void deleteFirstOccurrenceText(const std::string& pattern) {
        if (pattern.size() > text.size())
            return;
        text.replace(text.find(pattern), pattern.size(), "");
        updateSFMLText();
    }
};

std::pair<std::string, int> menu(sf::RenderWindow& app) {
    sf::View view(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    view.setViewport(sf::FloatRect(0, 0, 1, 1));

    app.setView(view);

    // The quantity of generations in L system
    auto fractalsTextField = new TextField("Fractals: ", 100, 100, 300, 50);
    auto gensNumberTextField = new TextField("Generations number: (input from keyboard)", 100, 50, 30, 50);
    auto warningTextField = new TextField(100 + 230, 50, 300, 50);

    bool isStringInputFromKeyboard = true;

    TextButton *triangleTextButton, *kochsTextButton, *plantTextButton, *curveTextButton;

    triangleTextButton = new TextButton("Sierpinski triangle",120, 140, 300, 50);
    kochsTextButton = new TextButton("Koch's snowflake",120, 190, 300, 50);
    plantTextButton = new TextButton("Plant",120, 240, 300, 50);
    curveTextButton = new TextButton("Dragon curve",120, 290, 300, 50);

    int untouchableSymbols = gensNumberTextField->getTextSize() - (int)std::string("(input from keyboard)").size();

    bool isWarning = false;
    while (app.isOpen()) {
        triangleTextButton->changeColorOnHover();
        kochsTextButton->changeColorOnHover();
        plantTextButton->changeColorOnHover();
        curveTextButton->changeColorOnHover();

        sf::Event event;
        while (app.pollEvent(event)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(app);

            triangleTextButton->changeFocusOnHover(mousePosition);
            kochsTextButton->changeFocusOnHover(mousePosition);
            plantTextButton->changeFocusOnHover(mousePosition);
            curveTextButton->changeFocusOnHover(mousePosition);

            switch (event.type) {
                case sf::Event::Closed:
                    app.close();
                    break;
                case sf::Event::MouseButtonPressed: {
                    if (isStringInputFromKeyboard)
                        break;
                    std::string input_number = gensNumberTextField->getText().substr(untouchableSymbols,
                                                                                     gensNumberTextField->getTextSize() - untouchableSymbols);
                    int gensNumber = atoi(input_number.c_str());

                    if (triangleTextButton->haveFocus()) {
                        if (gensNumber <= 0) {
                            isWarning = true;
                            warningTextField->setText("<--- Incorrect input");
                        } else if (gensNumber >= 15) {
                            isWarning = true;
                            warningTextField->setText("<--- Too big number");
                        } else {
                            isWarning = false;

                            return std::make_pair(triangleTextButton->getText(), gensNumber);
                        }
                    } else if (kochsTextButton->haveFocus()) {
                        if (gensNumber <= 0) {
                            isWarning = true;
                            warningTextField->setText("<--- Incorrect input");
                        } else if (gensNumber >= 11) {
                            isWarning = true;
                            warningTextField->setText("<--- Too big number");
                        } else {
                            isWarning = false;
                            return std::make_pair(kochsTextButton->getText(), gensNumber);
                        }
                    } else if (plantTextButton->haveFocus()) {
                        if (gensNumber <= 0) {
                            isWarning = true;
                            warningTextField->setText("<--- Incorrect input");
                        } else if (gensNumber >= 11) {
                            isWarning = true;
                            warningTextField->setText("<--- Too big number");
                        } else {
                            isWarning = false;
                            return std::make_pair(plantTextButton->getText(), gensNumber);
                        }
                    } else if (curveTextButton->haveFocus()) {
                        if (gensNumber <= 0) {
                            isWarning = true;
                            warningTextField->setText("<--- Incorrect input");
                        } else if (gensNumber >= 21) {
                            isWarning = true;
                            warningTextField->setText("<--- Too big number");
                        } else {
                            isWarning = false;
                            return std::make_pair(curveTextButton->getText(), gensNumber);
                        }
                    }
                    break;
                }
                case sf::Event::TextEntered: {
                    if (isStringInputFromKeyboard) {
                        isStringInputFromKeyboard = false;
                        gensNumberTextField->deleteFirstOccurrenceText("(input from keyboard)");
                    }

                    int dec_unicode = event.text.unicode;

                    // Unicode for digits
                    if (dec_unicode >= 48 and dec_unicode <= 57 and
                        gensNumberTextField->getTextSize() < untouchableSymbols + 2) {
                        gensNumberTextField->addCharacter(char(dec_unicode));
                    }

                    // Handle Delete button
                    if (dec_unicode == 8 and gensNumberTextField->getTextSize() > untouchableSymbols) {
                        gensNumberTextField->deleteLastCharacter();
                    }
                    break;
                }
            }
        }

        app.clear(sf::Color::White);

        app.draw(fractalsTextField->getSFMLText());
        app.draw(gensNumberTextField->getSFMLText());

        app.draw(triangleTextButton->getSFMLText());
        app.draw(kochsTextButton->getSFMLText());
        app.draw(plantTextButton->getSFMLText());
        app.draw(curveTextButton->getSFMLText());

        if (isWarning)
            app.draw(warningTextField->getSFMLText());

        app.display();
    }
}

void fillColorFigure(sf::VertexArray& figure, sf::Color color) {
    for (int i = 0; i < figure.getVertexCount(); ++i) {
        figure[i].color = color;
    }
}

void makeFigure(sf::VertexArray& figure, LSystem* lSystem, Robot* robot, const std::string& robotName, int gensNumber) {

    robot = new Robot(robotName, 0, HEIGHT, 1, HEIGHT);
    if (robotName == "Plant") {
        lSystem = new LSystem("X", 'X', 'F', "F-[[X]+X]+F[+FX]-X", "FF", 25, gensNumber);
        robot->rotate(45);
    } else if (robotName == "Sierpinski triangle") {
        lSystem = new LSystem("A", 'A', 'B', "B-A-B", "A+B+A", 60, gensNumber);
    } else if (robotName == "Dragon curve") {
        lSystem = new LSystem("FX", 'X', 'Y', "X+YF+", "-FX-Y", 90, gensNumber);
    } else if (robotName == "Koch's snowflake") {
        lSystem = new LSystem("F++F++F", 'F', "F-F++F-F", 60, gensNumber);
    }

    figure.clear();

    RobotData newPos;
    for (char c : lSystem->getAxiom()) {
        if (c == lSystem->getChr1()) {
            figure.append(sf::Vector2f(robot->getBeginX(), robot->getBeginY()));
            robot->move();
        } else if (c == lSystem->getChr2()) {
            figure.append(sf::Vector2f(robot->getBeginX(), robot->getBeginY()));
            robot->move();
        } else if (c == '-') {
            robot->rotate(+lSystem->getAngle());
        } else if (c == '+') {
            robot->rotate(-lSystem->getAngle());
        } else if (c == '[') {
            if (robotName == "Plant") {
                robot->getMemory()->push({robot->getBeginX(), robot->getBeginY(), robot->getAngle()});
            }
        } else if (c == ']') {
            if (robotName == "Plant") {
                newPos = robot->getMemory()->top();
                robot->getMemory()->pop();
                robot->setBeginX(newPos.x);
                robot->setBeginY(newPos.y);
                robot->setAngle(newPos.angle);
            }
        }
    }

    // Add last vertex
    figure.append(sf::Vector2f(robot->getBeginX(), robot->getBeginY()));

    if (robotName == "Dragon curve") {
        fillColorFigure(figure, sf::Color::Red);
    } else if (robotName == "Koch's snowflake"){
        fillColorFigure(figure, sf::Color::Blue);
    } else if (robotName == "Plant") {
        fillColorFigure(figure, sf::Color::Green);
    } else if (robotName == "Sierpinski triangle") {
        fillColorFigure(figure, sf::Color::Green);
    }
}

int main() {
//    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT,64),"Fractal");
//    sf::View view = app.getDefaultView();
//
//    std::pair<std::string, int> robotNameAndGensNumber = menu(app);
//    std::string robotName = robotNameAndGensNumber.first;
//    int gensNumber = robotNameAndGensNumber.second;

    Robot* robot;
    LSystem *LSystem;
    sf::VertexArray figure(sf::LinesStrip);

    makeFigure(figure, LSystem, robot, "Plant", 10);

//    sf::Texture loupeTexture;
//    loupeTexture.loadFromFile("./img/loupe.png");
//    sf::Sprite loupeSprite;
//    loupeSprite.setTexture(loupeTexture);
//    loupeSprite.setPosition(WIDTH - 200, 100);
//
//    sf::CircleShape circle(50);
//    circle.setFillColor(sf::Color(100, 250, 50));
//
//    sf::Vector2f oldPos = sf::Vector2f(0, 0);
//    bool moving = false;
//    bool after_menu = false;
//    float zoom = 1;
//    bool isLoupe = false;
//    while(app.isOpen()){
//        sf::Event event;
//        while(app.pollEvent(event)) {
//            switch (event.type) {
//                case sf::Event::KeyPressed:
//                    if (event.key.code == sf::Keyboard::Escape) {
//                        std::pair<std::string, int> newRobotNameAndNewGensNumber = menu(app);
//                        const std::string newRobotName = newRobotNameAndNewGensNumber.first;
//                        int newGensNumber = newRobotNameAndNewGensNumber.second;
//                        after_menu = true;
//
//                        oldPos = sf::Vector2f(0, 0);
//                        makeFigure(figure, LSystem, robot, newRobotName, newGensNumber);
//                    }
//
//                    break;
//                case sf::Event::Closed:
//                    app.close();
//                    break;
//                case sf::Event::MouseButtonPressed:
//                    moving = true;
//                    oldPos = app.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
//                    break;
//                case sf::Event::MouseButtonReleased:
//                    moving = false;
//                    oldPos = app.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
//                    break;
//                case sf::Event::MouseMoved: {
//                    if (!moving)
//                        break;
//
//                    sf::Vector2f newPos = app.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
//
//                    sf::Vector2f deltaPos = newPos - oldPos;
//
//
//                    if (after_menu) {
//                        view.setCenter(sf::Vector2f(WIDTH / 2, HEIGHT / 2));
//                        after_menu = false;
//                    } else {
//                        view.setCenter(view.getCenter() - deltaPos);
//                    }
//
//                    app.setView(view);
//
//                    oldPos = app.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
//                    break;
//                } case sf::Event::MouseWheelScrolled: {
//                    if (moving)
//                        break;
//
//                    if (event.mouseWheelScroll.delta >= 1) {
//                        zoom = std::max(0.5f, zoom - 0.1f);
//
//                    } else if (event.mouseWheelScroll.delta <= -1) {
//                        zoom = std::min(2.f, zoom + 0.1f);
//                    }
//
//                    isLoupe = true;
//
//                    view.setSize(app.getDefaultView().getSize());
//                    view.zoom(zoom);
//
//                    app.setView(view);
//
//
//                    break;
//                }
//           }
//        }
//
//        app.clear(sf::Color::Black);
//
//        app.draw(figure);
//
//        // TO DO
//        if (isLoupe) {
//            isLoupe = false;
//            app.draw(loupeSprite);
//        }
//        app.display();
//    }

    return 0;
}