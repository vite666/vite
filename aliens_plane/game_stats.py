# -*- coding: utf-8 -*-

'游戏数据库'

__author__='ViTe-志尊威少'
import json
class GameStats():
    def __init__(self,ai_settings):
        self.ai_settings=ai_settings
        self.reset_stats()
        self.game_active=False
        with open('data.txt','rb')as f:
            self.high_score=json.load(f)

    def reset_stats(self):
        self.ships_left=self.ai_settings.ship_limit
        self.score=0
        self.level=1
