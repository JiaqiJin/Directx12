#pragma once

#include "../Core/Application.h"

#include <memory>

class TestDemos : public Kawaii::Application
{
public:
    TestDemos();
    ~TestDemos();

    void init_app()                override;
    void input()                   override;
    void update(double delta_time) override;
    void render()                  override;
};

TestDemos::TestDemos()
{

}

TestDemos::~TestDemos()
{

}

void TestDemos::init_app()
{

}

void TestDemos::input()
{

}

void TestDemos::update(double delta_time)
{

}

void TestDemos::render()
{

}