#include <iostream>
#include <string>
#include <vector>

class UIElement {
public:
    UIElement(const std::string& id, int x, int y) : id_(id), x_(x), y_(y) {}
    virtual ~UIElement() {}

    virtual void draw() = 0;
    void setPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }

    const std::string& getId() const { return id_; }
    int getX() const { return x_; }
    int getY() const { return y_; }

protected:
    std::string id_;
    int x_;
    int y_;
};

class Button : public UIElement {
public:
    Button(const std::string& id, int x, int y, const std::string& label)
        : UIElement(id, x, y), label_(label) {}

    void draw() override {
        std::cout << "Button: ID=" << id_ << ", Position=(" << x_ << ", " << y_
                  << "), Label=" << label_ << std::endl;
    }

private:
    std::string label_;
};

class TextField : public UIElement {
public:
    TextField(const std::string& id, int x, int y, const std::string& text)
        : UIElement(id, x, y), text_(text) {}

    void draw() override {
        std::cout << "TextField: ID=" << id_ << ", Position=(" << x_ << ", " << y_
                  << "), Text=" << text_ << std::endl;
    }

private:
    std::string text_;
};

class Label : public UIElement {
public:
    Label(const std::string& id, int x, int y, const std::string& text)
        : UIElement(id, x, y), text_(text) {}

    void draw() override {
        std::cout << "Label: ID=" << id_ << ", Position=(" << x_ << ", " << y_
                  << "), Text=" << text_ << std::endl;
    }

private:
    std::string text_;
};


class GUI {
public:
    void addElement(UIElement* element) {
        elements_.push_back(element);
    }

    void drawAll() {
        for (UIElement* element : elements_) {
            element->draw();
        }
    }

    ~GUI() {
        for (UIElement* element : elements_) {
            delete element;
        }
    }

private:
    std::vector<UIElement*> elements_;
};

int main() {
    GUI gui;

    UIElement* button1 = new Button("button1", 10, 20, "Click Me!");
    UIElement* textField1 = new TextField("textField1", 50, 100, "Enter text here");
    UIElement* label1 = new Label("label1", 150, 50, "This is a label");

    gui.addElement(button1);
    gui.addElement(textField1);
    gui.addElement(label1);

    gui.drawAll();

    return 0;
}