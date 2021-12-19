#ifndef __STRUCTS_H__
#define __STRUCTS_H__



struct spritetype
{
    int x;
    int y;
    int z;
    __int16 cstat;
    __int16 picnum;
    char shade;
    unsigned __int8 pal;
    unsigned __int8 clipdist;
    unsigned __int8 filler;
    unsigned __int8 xrepeat;
    unsigned __int8 yrepeat;
    char xoffset;
    char yoffset;
    __int16 sectnum;
    __int16 statnum;
    __int16 ang;
    __int16 owner;
    __int16 xvel;
    __int16 yvel;
    __int16 zvel;
    __int16 lotag;
    __int16 hitag;
    __int16 extra;
};


struct PANEL_SPRITE_OVERLAY
{
    struct PANEL_STATEstruct * State;
    int flags;
    __int16 tics;
    __int16 pic;
    __int16 xoff;
    __int16 yoff;
};


struct PANEL_SPRITEstruct
{
    struct PANEL_SPRITEstruct * Next;
    struct PANEL_SPRITEstruct * Prev;
    struct PANEL_SPRITEstruct * sibling;
    struct PANEL_STATEstruct * State;
    struct PANEL_STATEstruct * RetractState;
    struct PANEL_STATEstruct * PresentState;
    struct PANEL_STATEstruct * ActionState;
    struct PANEL_STATEstruct * RestState;
    struct PLAYERstruct * PlayerP;
    unsigned __int16 xfract;
    __int16 x;
    unsigned __int16 yfract;
    __int16 y;
    struct PANEL_SPRITE_OVERLAY over[8];
    void(__cdecl * PanelSpriteFunc)(struct PANEL_SPRITEstruct *);
    __int16 ID;
    __int16 picndx;
    __int16 picnum;
    __int16 x1;
    __int16 y1;
    __int16 x2;
    __int16 y2;
    __int16 vel;
    __int16 vel_adj;
    __int16 numpages;
    int xorig;
    int yorig;
    int flags;
    int priority;
    int scale;
    int jump_speed;
    int jump_grav;
    int xspeed;
    __int16 tics;
    __int16 delay;
    __int16 ang;
    __int16 rotate_ang;
    __int16 sin_ndx;
    __int16 sin_amt;
    __int16 sin_arc_speed;
    __int16 bob_height_shift;
    __int16 shade;
    __int16 pal;
    __int16 kill_tics;
    __int16 WeaponType;
};


struct __declspec(align(4)) PANEL_STATEstruct
{
  __int16 picndx;
  int tics;
  void (__cdecl *Animator)(struct PANEL_SPRITEstruct *);
  struct PANEL_STATEstruct *NextState;
  unsigned int flags;
  unsigned __int8 xvel;
  unsigned __int8 yvel;
};


struct SW_PACKET
{
    __int16 vel;
    __int16 svel;
    char angvel;
    char aimvel;
    int bits;
};


struct ATTRIBUTEstruct
{
    __int16 Speed[4];
    char TicAdjust[4];
    unsigned __int8 MaxWeapons;
    int Sounds[11];
};



struct walltype
{
    int x;
    int y;
    __int16 point2;
    __int16 nextwall;
    __int16 nextsector;
    __int16 cstat;
    __int16 picnum;
    __int16 overpicnum;
    char shade;
    unsigned __int8 pal;
    unsigned __int8 xrepeat;
    unsigned __int8 yrepeat;
    unsigned __int8 xpanning;
    unsigned __int8 ypanning;
    __int16 lotag;
    __int16 hitag;
    __int16 extra;
};


struct STATEstruct
{
    __int16 Pic;
    int Tics;
    int(__cdecl * Animator)(__int16);
    struct STATEstruct * NextState;
};


struct sectortype
{
    __int16 wallptr;
    __int16 wallnum;
    int ceilingz;
    int floorz;
    __int16 ceilingstat;
    __int16 floorstat;
    __int16 ceilingpicnum;
    __int16 ceilingheinum;
    char ceilingshade;
    unsigned __int8 ceilingpal;
    unsigned __int8 ceilingxpanning;
    unsigned __int8 ceilingypanning;
    __int16 floorpicnum;
    __int16 floorheinum;
    char floorshade;
    unsigned __int8 floorpal;
    unsigned __int8 floorxpanning;
    unsigned __int8 floorypanning;
    unsigned __int8 visibility;
    unsigned __int8 filler;
    __int16 lotag;
    __int16 hitag;
    __int16 extra;
};


struct $E74BD3BE005148E4B5EBDE42A1C432CC
{
    struct PANEL_SPRITEstruct * Next;
    struct PANEL_SPRITEstruct * Prev;
};


struct DECISION
{
    __int16 range;
    int(__cdecl * action)(__int16);
};


struct PERSONALITYstruct
{
    struct DECISION * Battle;
    struct DECISION * Offense;
    struct DECISION * Broadcast;
    struct DECISION * Surprised;
    struct DECISION * Evasive;
    struct DECISION * LostTarget;
    struct DECISION * CloseRange;
    struct DECISION * TouchTarget;
};


struct ROTATOR
{
    int pos;
    int open_dest;
    int tgt;
    int speed;
    int orig_speed;
    int vel;
    int num_walls;
    int * origx;
    int * origy;
};


struct ACTOR_ACTION_SET
{
    struct STATEstruct ** Stand;
    struct STATEstruct ** Run;
    struct STATEstruct ** Jump;
    struct STATEstruct ** Fall;
    struct STATEstruct ** Crawl;
    struct STATEstruct ** Swim;
    struct STATEstruct ** Fly;
    struct STATEstruct ** Rise;
    struct STATEstruct ** Sit;
    struct STATEstruct ** Look;
    struct STATEstruct ** Climb;
    struct STATEstruct ** Pain;
    struct STATEstruct ** Death1;
    struct STATEstruct ** Death2;
    struct STATEstruct ** Dead;
    struct STATEstruct ** DeathJump;
    struct STATEstruct ** DeathFall;
    struct STATEstruct ** CloseAttack[2];
    __int16 CloseAttackPercent[2];
    struct STATEstruct ** Attack[6];
    __int16 AttackPercent[6];
    struct STATEstruct ** Special[2];
    struct STATEstruct ** Duck;
    struct STATEstruct ** Dive;
};


struct __declspec(align(4)) SECTOR_OBJECTstruct
{
    struct sectortype * sectp[40];
    void(__cdecl * PreMoveAnimator)(struct SECTOR_OBJECTstruct *);
    void(__cdecl * PostMoveAnimator)(struct SECTOR_OBJECTstruct *);
    void(__cdecl * Animator)(struct SECTOR_OBJECTstruct *);
    struct spritetype * controller;
    struct spritetype * sp_child;
    int xmid;
    int ymid;
    int zmid;
    int vel;
    int vel_tgt;
    int player_xoff;
    int player_yoff;
    int zorig_floor[40];
    int zorig_ceiling[40];
    int zdelta;
    int z_tgt;
    int z_rate;
    int update;
    int bob_diff;
    int target_dist;
    int floor_loz;
    int floor_hiz;
    int morph_z;
    int morph_z_min;
    int morph_z_max;
    int bob_amt;
    int drive_angspeed;
    int drive_angslide;
    int drive_speed;
    int drive_slide;
    int crush_z;
    int flags;
    __int16 sector[40];
    __int16 sp_num[60];
    __int16 xorig[600];
    __int16 yorig[600];
    __int16 sectnum;
    __int16 mid_sector;
    __int16 max_damage;
    __int16 ram_damage;
    __int16 wait_tics;
    __int16 num_sectors;
    __int16 num_walls;
    __int16 track;
    __int16 point;
    __int16 vel_rate;
    __int16 dir;
    __int16 ang;
    __int16 ang_moving;
    __int16 clipdist;
    __int16 clipbox_dist[32];
    __int16 clipbox_xoff[32];
    __int16 clipbox_yoff[32];
    __int16 clipbox_ang[32];
    __int16 clipbox_vdist[32];
    __int16 clipbox_num;
    __int16 ang_tgt;
    __int16 ang_orig;
    __int16 last_ang;
    __int16 old_ang;
    __int16 spin_speed;
    __int16 spin_ang;
    __int16 turn_speed;
    __int16 bob_sine_ndx;
    __int16 bob_speed;
    __int16 op_main_sector;
    __int16 save_vel;
    __int16 save_spin_speed;
    __int16 match_event;
    __int16 match_event_sprite;
    __int16 scale_type;
    __int16 scale_active_type;
    __int16 scale_dist;
    __int16 scale_speed;
    __int16 scale_dist_min;
    __int16 scale_dist_max;
    __int16 scale_rand_freq;
    __int16 scale_point_dist[600];
    __int16 scale_point_speed[600];
    __int16 scale_point_base_speed;
    __int16 scale_point_dist_min;
    __int16 scale_point_dist_max;
    __int16 scale_point_rand_freq;
    __int16 scale_x_mult;
    __int16 scale_y_mult;
    __int16 morph_wall_point;
    __int16 morph_ang;
    __int16 morph_speed;
    __int16 morph_dist_max;
    __int16 morph_rand_freq;
    __int16 morph_dist;
    __int16 morph_z_speed;
    __int16 morph_xoff;
    __int16 morph_yoff;
    __int16 limit_ang_center;
    __int16 limit_ang_delta;
};


struct REMOTE_CONTROL
{
    __int16 cursectnum;
    __int16 lastcursectnum;
    __int16 pang;
    __int16 filler;
    int xvect;
    int yvect;
    int oxvect;
    int oyvect;
    int slide_xvect;
    int slide_yvect;
    int posx;
    int posy;
    int posz;
    struct SECTOR_OBJECTstruct * sop_control;
};


struct PLAYERstruct
{
    int posx;
    int posy;
    int posz;
    int oposx;
    int oposy;
    int oposz;
    __int16 oang;
    __int16 ohoriz;
    __int16 lv_sectnum;
    int lv_x;
    int lv_y;
    int lv_z;
    struct spritetype * remote_sprite;
    struct REMOTE_CONTROL remote;
    struct SECTOR_OBJECTstruct * sop_remote;
    struct SECTOR_OBJECTstruct * sop;
    int jump_count;
    int jump_speed;
    __int16 down_speed;
    __int16 up_speed;
    int z_speed;
    int oz_speed;
    int climb_ndx;
    int hiz;
    int loz;
    int ceiling_dist;
    int floor_dist;
    struct sectortype * hi_sectp;
    struct sectortype * lo_sectp;
    struct spritetype * hi_sp;
    struct spritetype * lo_sp;
    struct spritetype * last_camera_sp;
    int camera_dist;
    int circle_camera_dist;
    int six;
    int siy;
    int siz;
    __int16 siang;
    int xvect;
    int yvect;
    int oxvect;
    int oyvect;
    int friction;
    int slide_xvect;
    int slide_yvect;
    __int16 slide_ang;
    int slide_dec;
    int drive_angvel;
    int drive_oangvel;
    int scr_x;
    int scr_y;
    int oscr_x;
    int oscr_y;
    int scr_xvect;
    int scr_yvect;
    __int16 scr_ang;
    __int16 oscr_ang;
    __int16 scr_sectnum;
    __int16 view_outside_dang;
    __int16 circle_camera_ang;
    __int16 camera_check_time_delay;
    __int16 pang;
    __int16 cursectnum;
    __int16 lastcursectnum;
    __int16 turn180_target;
    int horizbase;
    int horiz;
    int horizoff;
    int hvel;
    int tilt;
    int tilt_dest;
    __int16 recoil_amt;
    __int16 recoil_speed;
    __int16 recoil_ndx;
    __int16 recoil_horizoff;
    int oldposx;
    int oldposy;
    int oldposz;
    int RevolveX;
    int RevolveY;
    __int16 RevolveDeltaAng;
    __int16 RevolveAng;
    __int16 PlayerSprite;
    __int16 PlayerUnderSprite;
    struct spritetype * SpriteP;
    struct spritetype * UnderSpriteP;
    __int16 pnum;
    __int16 LadderSector;
    __int16 LadderAngle;
    int lx;
    int ly;
    __int16 JumpDuration;
    __int16 WadeDepth;
    __int16 bob_amt;
    __int16 bob_ndx;
    __int16 bcnt;
    int bob_z;
    struct SW_PACKET input;
    struct SW_PACKET inputfifo[256];
    int movefifoend;
    int myminlag;
    int syncvalhead;
    unsigned __int8 syncval[1024][16];
    int playerreadyflag;
    void(__cdecl * DoPlayerAction)(struct PLAYERstruct *);
    int Flags;
    int Flags2;
    int KeyPressFlags;
    struct SECTOR_OBJECTstruct * sop_control;
    struct SECTOR_OBJECTstruct * sop_riding;
    struct $E74BD3BE005148E4B5EBDE42A1C432CC PanelSpriteList;
    unsigned __int8 HasKey[8];
    __int16 SwordAng;
    int WpnGotOnceFlags;
    int WpnFlags;
    __int16 WpnAmmo[14];
    __int16 WpnNum;
    struct PANEL_SPRITEstruct * CurWpn;
    struct PANEL_SPRITEstruct * Wpn[14];
    struct PANEL_SPRITEstruct * Chops;
    unsigned __int8 WpnRocketType;
    unsigned __int8 WpnRocketHeat;
    unsigned __int8 WpnRocketNuke;
    unsigned __int8 WpnFlameType;
    unsigned __int8 WpnFirstType;
    unsigned __int8 WeaponType;
    __int16 FirePause;
    __int16 InventoryNum;
    __int16 InventoryBarTics;
    struct PANEL_SPRITEstruct * InventorySprite[7];
    struct PANEL_SPRITEstruct * InventorySelectionBox;
    struct PANEL_SPRITEstruct * MiniBarHealthBox;
    struct PANEL_SPRITEstruct * MiniBarAmmo;
    struct PANEL_SPRITEstruct * MiniBarHealthBoxDigit[3];
    struct PANEL_SPRITEstruct * MiniBarAmmoDigit[3];
    __int16 InventoryTics[7];
    __int16 InventoryPercent[7];
    char InventoryAmount[7];
    unsigned __int8 InventoryActive[7];
    __int16 DiveTics;
    __int16 DiveDamageTics;
    __int16 DeathType;
    __int16 Kills;
    __int16 Killer;
    __int16 KilledPlayer[8];
    __int16 SecretsFound;
    __int16 Armor;
    __int16 MaxHealth;
    char PlayerName[32];
    unsigned __int8 UziShellLeftAlt;
    unsigned __int8 UziShellRightAlt;
    unsigned __int8 TeamColor;
    __int16 FadeTics;
    __int16 FadeAmt;
    unsigned __int8 NightVision;
    unsigned __int8 StartColor;
    unsigned __int8 temp_pal[768];
    unsigned __int8 IsAI;
    __int16 fta;
    __int16 ftq;
    __int16 NumFootPrints;
    unsigned __int8 PlayerTalking;
    int TalkVocnum;
    int TalkVocHandle;
    unsigned __int8 WpnUziType;
    unsigned __int8 WpnShotgunType;
    unsigned __int8 WpnShotgunAuto;
    unsigned __int8 WpnShotgunLastShell;
    unsigned __int8 WpnRailType;
    unsigned __int8 Bloody;
    int nukevochandle;
    unsigned __int8 InitingNuke;
    unsigned __int8 TestNukeInit;
    unsigned __int8 NukeInitialized;
    __int16 FistAng;
    unsigned __int8 WpnKungFuMove;
    unsigned __int8 BunnyMode;
    __int16 HitBy;
    __int16 Reverb;
    __int16 Heads;
    int PlayerVersion;
};


struct __declspec(align(4)) USER
{
    struct ROTATOR * rotator;
    int WallCount;
    char * WallShade;
    struct walltype * WallP;
    struct STATEstruct * State;
    struct STATEstruct ** Rot;
    struct STATEstruct * StateStart;
    struct STATEstruct * StateEnd;
    struct STATEstruct ** StateFallOverride;
    int(__cdecl * ActorActionFunc)(__int16);
    struct ACTOR_ACTION_SET * ActorActionSet;
    struct PERSONALITYstruct * Personality;
    struct ATTRIBUTEstruct * Attrib;
    struct SECTOR_OBJECTstruct * sop_parent;
    int ox;
    int oy;
    int oz;
    int Flags;
    int Flags2;
    int Tics;
    __int16 RotNum;
    __int16 ID;
    __int16 Health;
    __int16 MaxHealth;
    __int16 LastDamage;
    __int16 PainThreshold;
    __int16 jump_speed;
    __int16 jump_grav;
    __int16 ceiling_dist;
    __int16 floor_dist;
    __int16 lo_step;
    int hiz;
    int loz;
    int zclip;
    struct sectortype * hi_sectp;
    struct sectortype * lo_sectp;
    struct spritetype * hi_sp;
    struct spritetype * lo_sp;
    int active_range;
    __int16 SpriteNum;
    __int16 Attach;
    struct spritetype * SpriteP;
    struct PLAYERstruct * PlayerP;
    __int16 Sibling;
    int xchange;
    int ychange;
    int zchange;
    int z_tgt;
    int vel_tgt;
    __int16 vel_rate;
    unsigned __int8 speed;
    __int16 Counter;
    __int16 Counter2;
    __int16 Counter3;
    __int16 DamageTics;
    __int16 BladeDamageTics;
    __int16 WpnGoal;
    unsigned int Radius;
    int OverlapZ;
    __int16 flame;
    struct spritetype * tgt_sp;
    __int16 scale_speed;
    unsigned __int16 scale_value;
    __int16 scale_tgt;
    __int16 DistCheck;
    __int16 Dist;
    __int16 TargetDist;
    __int16 WaitTics;
    __int16 track;
    __int16 point;
    __int16 track_dir;
    int track_vel;
    __int16 slide_ang;
    int slide_vel;
    __int16 slide_dec;
    __int16 motion_blur_dist;
    __int16 motion_blur_num;
    __int16 wait_active_check;
    __int16 inactive_time;
    int sx;
    int sy;
    int sz;
    __int16 sang;
    unsigned __int8 spal;
    int ret;
    int Flag1;
    char LastWeaponNum;
    char WeaponNum;
    __int16 bounce;
    int ShellNum;
    __int16 FlagOwner;
    __int16 Vis;
    unsigned __int8 DidAlert;
};


#endif // __STRUCTS_H__
