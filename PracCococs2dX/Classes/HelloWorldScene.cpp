#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "HelloMenuLayer.h"

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
    
    
//    CCLabelAtlas *pLabelAtlas = CCLabelAtlas::create("0", "fonts_rankscore.png", 24, 38, (unsigned int)'/');
//    pLabelAtlas->setString("38475");
//    pLabelAtlas->setPosition(ccp(100,100));
////    this->addChild(pLabelAtlas,2);
//    
//    
//    CCLabelAtlas *pLabelAtlas1 = CCLabelAtlas::create("0", "fonts_ranking_01.png", 40, 46, (unsigned int)'0');
//    pLabelAtlas1->setString("38475");
//    pLabelAtlas1->setPosition(ccp(200,200));
////    this->addChild(pLabelAtlas1,2);
//    
//    CCLabelAtlas *pLabelAtlas2 = CCLabelAtlas::create("0", "set1_player_hud3.png", 14, 21, (unsigned int)'0');
//    pLabelAtlas2->setString("38475:");
//    pLabelAtlas2->setPosition(ccp(300,100));
////    this->addChild(pLabelAtlas2,2);
//    
//    CCLabelAtlas *pLabelAtlas3 = CCLabelAtlas::create("00.0", "fps_images.png", 12, 32, (unsigned int)'.');
//    pLabelAtlas3->setString("385.7");
//    pLabelAtlas3->setPosition(ccp(400,100));
//    this->addChild(pLabelAtlas3,2);
    
//    
//    CCMenuItemLabel *pMenuLabelAtlas = CCMenuItemLabel::create(pLabel,
//                                                          this,
//                                                          menu_selector(HelloWorld::Test));
//    
//    
//    CCMenuItemImage *pMenuLabelAtlas1 = CCMenuItemImage::create("button_buy_01.png", this, menu_selector(HelloWorld::Test));
//    pMenuLabelAtlas1->setPosition(ccp(0,0));
//    pMenuLabelAtlas1->setAnchorPoint(ccp(0.5,0.5));
//    
//    CCMenuItemAtlasFont *pMenuAtlasFont = CCMenuItemAtlasFont::create("88", "fonts_rankscore.png", 24, 38, (unsigned int)'/', this, menu_selector(HelloWorld::Test));
//    pMenuAtlasFont->setPosition(ccp(400,400));
//    pMenuAtlasFont->setScale(4);
//    
//    
//    CCMenuItemFont *pMenuItemFont = CCMenuItemFont::create("Test", this, menu_selector(HelloWorld::Test));
//    pMenuItemFont->setPosition(ccp(500, 400));
//    pMenuItemFont->setScale(4);
//    
//    
//    CCMenuItemFont *p1 = CCMenuItemFont::create("Place", this, menu_selector(HelloWorld::Place));
//    CCMenuItemFont *p2 = CCMenuItemFont::create("Hide", this, menu_selector(HelloWorld::Hide));
//    CCMenuItemFont *p3 = CCMenuItemFont::create("Show", this, menu_selector(HelloWorld::Show));
//    CCMenuItemFont *p4 = CCMenuItemFont::create("Toggle", this, menu_selector(HelloWorld::Toggle));
//    CCMenuItemFont *p5 = CCMenuItemFont::create("Back", this, menu_selector(HelloWorld::Back));
//    
//    // create menu, it's an autorelease object
//    pMenu = CCMenu::create(
//                           p1,
//                           pMenuLabelAtlas1,
//                           NULL);
//    pMenu->alignItemsVerticallyWithPadding(30);
//    pMenu->setPosition( ccp(size.width / 2, size.height/2) );
//    this->addChild(pMenu, 1);
    
//    scheduleOnce(schedule_selector(HelloWorld::nextT), 2);

    // add "HelloWorld" splash screen"
    CCSprite* Sprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    Sprite->setPosition( ccp(size.width/2, size.height/2) );

    // add the sprite as a child to this layer
    this->addChild(Sprite, 0);
    
    
    
    pSprite = CCSprite::create("icon_05.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite,1);
    
    
    CCSprite *sp = CCSprite::create("icon_01.png");
//    addChild(sp);
    mProgressTimer = CCProgressTimer::create(sp);
    mProgressTimer->setPercentage(90);
    mProgressTimer->setPosition(ccp(size.width/2, size.height/2));
    
    addChild(mProgressTimer,10);
    schedule(schedule_selector(HelloWorld::update));
//    schedule(schedule_selector(HelloWorld::update), 1);
//    scheduleUpdate();
    setTouchEnabled(1);
    return true;
}

void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    
    pMenu->setHandlerPriority(2);
}

void HelloWorld::Place(CCObject* pSender)
{
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//    pSprite->runAction(CCPlace::create(ccp(size.width*CCRANDOM_0_1(),size.height*CCRANDOM_0_1())));
}

void HelloWorld::Hide(CCObject* pSender)
{
//    pSprite->runAction(CCHide::create());
    
    int numsRunAction = pSprite->numberOfRunningActions();
    CCLOG("running Action Numbers:%d",numsRunAction);
    if (numsRunAction > 0) {
        return;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCMoveTo *ac1 = CCMoveTo::create(2.0f, ccp(size.width-50,size.height-50));
    CCJumpTo *ac2 = CCJumpTo::create(5.0f, ccp(100,100), 20, 5);
    CCBlink *ac3 = CCBlink::create(3.0f, 3);
    CCAction *ac4 = CCTintBy::create(2.0f, 0, 255, 255);
    CCPlace *pl = CCPlace::create(ccp(size.width/2,size.height/2));
    
    CCCallFunc *cf = CCCallFunc::create(this, callfunc_selector(HelloWorld::Test));
    
    CCSequence *s1 = CCSequence::create(ac1,ac2,ac3,ac4,pl,cf,NULL);
    
//    CCSequence *ss = CCSequence::create(s1,CCDelayTime::create(5),s1->reverse(),NULL);
    
//    pSprite->runAction(CCRepeat::create(s1, 3));
//    pSprite->runAction(CCMoveTo::create(2, ccp(size.width*CCRANDOM_0_1(),size.height*CCRANDOM_0_1())));
    
    CCScaleTo *ac5 = CCScaleTo::create(5, 5);
    CCScaleBy *ac6 = CCScaleBy::create(5, 5);
    
    CCRotateTo *ac7 = CCRotateTo::create(5, 180);
    CCRotateBy *ac8 = CCRotateBy::create(5,180);
    
    CCSpawn *sp = CCSpawn::create(ac5,ac8,NULL);
    
    CCEaseBackInOut *eb = CCEaseBackInOut::create(ac1);
    pSprite->runAction(eb);
    
//    pSprite->runAction(sp);
}

void HelloWorld::update(float delta)
{
    float del = 100/60*delta*5;
    float percent = mProgressTimer->getPercentage();
    float total = del + percent;
    if (total > 100) {
        total = 0;
//        CCSprite *sp = CCSprite::create("icon_02");
//        mProgressTimer->setSprite(sp);
    }
    
    mProgressTimer->setPercentage(total);
}

void HelloWorld::Show(CCObject* pSender)
{
//    pSprite->runAction(CCShow::create());
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCRenderTexture *rt = CCRenderTexture::create(size.width, size.height);
    rt->begin();
//    this->visit();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    rt->end();
    
    CCSprite *tSp = CCSprite::createWithTexture(rt->getSprite()->getTexture());
    this->addChild(tSp);
    tSp->setPosition(ccp(size.width/2+10,size.height/2-10));
//    tSp->setRotation(180);
}

void HelloWorld::Toggle(CCObject* pSender)
{
    addChild(HelloMenuLayer::layer());
//    setTouchEnabled(false);
//    pSprite->runAction(CCToggleVisibility::create());
}

void HelloWorld::Back(CCObject* pSender)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCTMXTiledMap *map = CCTMXTiledMap::create("tileMap.tmx");
    addChild(map,2);
    map->setAnchorPoint(ccp(0.5,0.5));
    map->setPosition(ccp(size.width/2,size.height/2));
    map->setScale(3);
    
    CCTMXLayer* tLayer = map->layerNamed("Tile Layer 1");
    CCString *tStr1 = tLayer->propertyNamed("t1");
    CCLog("t1: ==%d",tStr1->intValue());
    
    CCString *tStr2 = tLayer->propertyNamed("t2");
    CCLog("t2 ==%s",tStr2->getCString());
    
    
    
    CCTMXLayer* tLayer2 = map->layerNamed("Tile Layer 2");
    CCString *tStr3 = tLayer2->propertyNamed("aa");
    CCLog("t3 ==%d",tStr3->intValue());
    CCString *tStr4 = tLayer2->propertyNamed("bb");
    CCLog("t4 ==%s",tStr4->getCString());
    
    CCLog("layerName ==%s",tLayer2->getLayerName());
    
    CCTMXLayer *tLayer4 = map->layerNamed("Tile Layer 4");
    CCSprite *tileSprite = tLayer4->tileAt(ccp(2,2));
    
    int gid = tLayer4->tileGIDAt(ccp(2,2));
    CCLog("gid ==%d",gid);
    
    
    CCLog("gid tt ==%d",tLayer->tileGIDAt(ccp(0,1)));
    CCLog("gid tt ==%d",tLayer->tileGIDAt(ccp(9,0)));
    CCLog("gid tt ==%d",tLayer->tileGIDAt(ccp(2,2)));
    CCLog("gid tt ==%d",tLayer->tileGIDAt(ccp(0,2)));
    CCLog("gid tt ==%d",tLayer->tileGIDAt(ccp(6,2)));
    CCLog("gid tt ==%d",tLayer->tileGIDAt(ccp(0,4)));
    
    
//    tLayer4->setTileGID(3, ccp(3,3));
    
    tileSprite->setScale(2);
    tileSprite->setPosition(ccp(300,300));
    
    
    
    tLayer4->removeTileAt(ccp(1,1));
    
    
    
    
    CCDictionary *tDic = map->propertiesForGID(1);
    
    
    CCTMXObjectGroup *ObjGroup = map->objectGroupNamed("Obj1");
    CCArray *tObjArray = ObjGroup->getObjects();
    
    CCDictionary *tDic1 = NULL;
    CCObject *pObjet = NULL;
    CCARRAY_FOREACH(tObjArray, pObjet)
    {
        tDic1 = (CCDictionary *)pObjet;
        if (!tDic1) {
            break;
        }
        
        CCDictElement *pDictElement = NULL;
        CCDICT_FOREACH(tDic1, pDictElement)
        {
            
            CCLog("fds");
        }
        
        
        
        CCLog("test aa");
    }
    
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

void HelloWorld::nextT()
{
    pMenu->setHandlerPriority(4);
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLog("HelloWorld ccTouchBegan");
    return true;
}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCLog("HelloWorld ccTouchesBegan");
}

void HelloWorld::registerWithTouchDispatcher(void)
{
    CCTouchDispatcher *disPatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    disPatcher->addTargetedDelegate(this, 3, 1);
    CCLog("registerWithTouchDispatcher");
}