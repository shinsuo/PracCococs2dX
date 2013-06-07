#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
//    this->addChild(pLabel, 1);
    
    
    CCLabelAtlas *pLabelAtlas = CCLabelAtlas::create("0", "fonts_rankscore.png", 24, 38, (unsigned int)'/');
    pLabelAtlas->setString("38475");
    pLabelAtlas->setPosition(ccp(100,100));
//    this->addChild(pLabelAtlas,2);
    
    
    CCLabelAtlas *pLabelAtlas1 = CCLabelAtlas::create("0", "fonts_ranking_01.png", 40, 46, (unsigned int)'0');
    pLabelAtlas1->setString("38475");
    pLabelAtlas1->setPosition(ccp(200,200));
//    this->addChild(pLabelAtlas1,2);
    
    CCLabelAtlas *pLabelAtlas2 = CCLabelAtlas::create("0", "set1_player_hud3.png", 14, 21, (unsigned int)'0');
    pLabelAtlas2->setString("38475:");
    pLabelAtlas2->setPosition(ccp(300,100));
//    this->addChild(pLabelAtlas2,2);
    
    CCLabelAtlas *pLabelAtlas3 = CCLabelAtlas::create("00.0", "fps_images.png", 12, 32, (unsigned int)'.');
    pLabelAtlas3->setString("385.7");
    pLabelAtlas3->setPosition(ccp(400,100));
//    this->addChild(pLabelAtlas3,2);
    
    
    CCMenuItemLabel *pMenuLabelAtlas = CCMenuItemLabel::create(pLabel,
                                                          this,
                                                          menu_selector(HelloWorld::Test));
    
    
    CCMenuItemImage *pMenuLabelAtlas1 = CCMenuItemImage::create("button_buy_01.png", "button_buy_02.png", this, menu_selector(HelloWorld::Test));
    pMenuLabelAtlas1->setPosition(ccp(300,300));
   
    
    CCMenuItemAtlasFont *pMenuAtlasFont = CCMenuItemAtlasFont::create("88", "fonts_rankscore.png", 24, 38, (unsigned int)'/', this, menu_selector(HelloWorld::Test));
    pMenuAtlasFont->setPosition(ccp(400,400));
    pMenuAtlasFont->setScale(4);
    
    
    CCMenuItemFont *pMenuItemFont = CCMenuItemFont::create("Test", this, menu_selector(HelloWorld::Test));
    pMenuItemFont->setPosition(ccp(500, 400));
    pMenuItemFont->setScale(4);
    
    
    CCMenuItemFont *p1 = CCMenuItemFont::create("Place", this, menu_selector(HelloWorld::Place));
    CCMenuItemFont *p2 = CCMenuItemFont::create("Hide", this, menu_selector(HelloWorld::Hide));
    CCMenuItemFont *p3 = CCMenuItemFont::create("Show", this, menu_selector(HelloWorld::Show));
    CCMenuItemFont *p4 = CCMenuItemFont::create("Toggle", this, menu_selector(HelloWorld::Toggle));
    CCMenuItemFont *p5 = CCMenuItemFont::create("Back", this, menu_selector(HelloWorld::Back));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(p1,p2,p3,p4,p5, NULL);
    pMenu->alignItemsVerticallyWithPadding(30);
    pMenu->setPosition( ccp(800,320) );
    this->addChild(pMenu, 1);

    // add "HelloWorld" splash screen"
    pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    
    
    
    
    return true;
}

void HelloWorld::Place(CCObject* pSender)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pSprite->runAction(CCPlace::create(ccp(size.width*CCRANDOM_0_1(),size.height*CCRANDOM_0_1())));
}

void HelloWorld::Hide(CCObject* pSender)
{
    pSprite->runAction(CCHide::create());
}

void HelloWorld::Show(CCObject* pSender)
{
    pSprite->runAction(CCShow::create());
}

void HelloWorld::Toggle(CCObject* pSender)
{
    pSprite->runAction(CCToggleVisibility::create());
}

void HelloWorld::Back(CCObject* pSender)
{
    
}

void HelloWorld::Test(CCObject* pSender)
{
    CCLOG("this is a Test");
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
