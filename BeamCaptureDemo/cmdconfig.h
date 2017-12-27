#ifndef CMDCONFIG
#define CMDCONFIG
#include <configure/instrument.h>
#pragma pack(8)
typedef struct
{
    setup_ENCODER_TYPE eEncoderType  ;
    setup_ENCODER_MODE eEncoderMode  ;
    setup_ENCODER_POLARITY ePolarity ;

    double fMaxScanSpeed;
    double fResulotion  ;
    double fOrigin      ;

    double fScanStart   ;
    double fScanStop    ;
    double fScanStep    ;
} CONFIG_SCAN ;

typedef struct
{
    setup_LAW_TYPE eLawType     ;
    setup_FOCAL_TYPE eFocalType ;

    unsigned int uiAngleStart;		    // 0.1 degree
    unsigned int uiAngleStop ;			// focal law  angle setting
    unsigned int uiAngleStep ;			//

    unsigned int	uiElem_qty;			    // aperture setting
    unsigned int	uiFirst_tx_elem;		// first trigger element
    unsigned int	uiFirst_rx_elem;		// first receive element
    unsigned int	uiLast_tx_elem;		    // last  trigger element
    unsigned int	uiLast_rx_elem;		    // last  receive element
    unsigned int	uiElem_step;			// element step (linear scan)

    //###################################################
    double	fPositionStart;		            // focal depth
    //#######################               //
    double	fPositionEnd;		            // not available currently
    double	fPositionStep;		            // not available currently
    //###################################################
    double	fOffsetStart;		            // focal plane
    double	fDepthStart;		            //
    double	fOffsetEnd;			            //
    double	fDepthEnd;			            //
}CONFIG_FOCALLAW ;

#pragma pack()

//***************************************************************//
enum setup_MATERIAL_TYPE
{
                                     //   LW        SW
    setup_MATERIAL_ALUMINUM  = 0   , //{630000, 310000, "铝"},/* 0 */
    setup_MATERIAL_STEEL           , //{589000, 324000, "普通钢"},/* 1 */
    setup_MATERIAL_STEEL_STRAINLESS, //{580000, 310000, "不锈钢"},/* 2 */
    setup_MATERIAL_BRASS           , //{430000, 200000, "黄铜"},/* 3 */
    setup_MATERIAL_COPPER          , //{470000, 230000, "铜"},/* 4 */
    setup_MATERIAL_IRON            , //{590000, 320000, "铁"},/* 5 */
    setup_MATERIAL_LEAD            , //{220000, 220000, "铅"},/* 6 */
    setup_MATERIAL_NYLON           , //{260000, 260000, "尼龙"},/* 7 */
    setup_MATERIAL_SILVER          , //{360000, 160000, "银"},/* 8 */
    setup_MATERIAL_GOLD  		   , //{320000, 320000, "金"},/* 9 */
    setup_MATERIAL_ZINC            , //{420000, 240000, "锌"},/* 10 */
    setup_MATERIAL_TITANIUM        , //{610000, 310000, "钛"},/* 11 */
    setup_MATERIAL_TIN             , //{330000, 170000, "锡"},/* 12 */
    setup_MATERIAL_EXPOXYRESIN     , //{254000, 110000, "环氧树脂"},/* 13 */
    setup_MATERIAL_ICE             , //{400000, 200000, "冰"},/* 14 */
    setup_MATERIAL_NICKEL          , //{560000, 300000, "镍"},/* 15 */
    setup_MATERIAL_PLEXIGLASS      , //{270000, 146000, "树脂玻璃"},/* 16 */
    setup_MATERIAL_POLYSTYRENE     , //{240000, 115000, "聚苯乙烯"},/* 17 */
    setup_MATERIAL_PORCELAIN       , //{584200, 584200, "瓷器"},/* 18 */
    setup_MATERIAL_PVC             , //{238800, 238800, "聚氯乙烯"},/* 19 */
    setup_MATERIAL_QUARTZGLASS     , //{563900, 563900, "石英玻璃"},/* 20 */
    setup_MATERIAL_RUBBERVULCANIZED, //{231100, 231100, "硫化橡胶"},/* 21 */
    setup_MATERIAL_TEFLON          , //{140000, 140000, "聚四氟乙烯"},/* 22 */
    setup_MATERIAL_WATER           , //{148000, 148000, "水"}	/* 23 */
} ;

typedef struct
{
    setup_PROBE_ANGLE     eSkew ;
    setup_MATERIAL_TYPE   eMaterial    ;
    double        fThickness  ;  // PART thickness , unit : mm
    double        fScanOffset  ;   //   scan axis offset
    double        fIndexOffset ;   //   index axis offset


} CONFIG_PART_INFO;

enum COMMAND
{
    CMD_NONE =  0 ,
    CMD_RESET_ALL  ,
    CMD_RESET_ENCODER  ,
    CMD_SET_CURRENT_GROUP ,
    CMD_GET_STATUS_INFO ,
    CMD_ADD_GROUP ,
    CMD_DEL_GROUP ,
    CMD_SET_ENCODER_TYPE,
    CMD_GET_CONFIG_SCAN ,
    CMD_SET_CONFIG_SCAN ,
    CMD_GET_CONFIG_FOCALLAW = 10,
    CMD_SET_CONFIG_FOCALLAW ,
    CMD_GET_CONFIG_PROBE ,
    CMD_SET_CONFIG_PROBE ,
    CMD_GET_CONFIG_WEDGE ,
    CMD_SET_CONFIG_WEDGE ,
    CMD_GET_CONFIG_PART  ,
    CMD_SET_CONFIG_PART  ,
    CMD_GET_CONFIG_UT_GENERAL ,
    CMD_SET_CONFIG_UT_GENERAL ,
    CMD_GET_CONFIG_UT_PULSER = 20 ,
    CMD_SET_CONFIG_UT_PULSER  ,
    CMD_GET_CONFIG_UT_RECEIVER,
    CMD_SET_CONFIG_UT_RECEIVER,
    CMD_GET_CONFIG_UT_ADVANCED ,
    CMD_SET_CONFIG_UT_ADVANCED ,
    CMD_GET_CONFIG_GATE_INFO   ,
    CMD_SET_CONFIG_GATE_INFO   ,
    CMD_GET_CONFIG_DISPLAY_INFO  ,
    CMD_SET_CONFIG_DISPLAY_INFO  ,
    CMD_GET_GROUP_BEAMDELAY = 30 ,
    CMD_SET_GROUP_BEAMDELAY    ,
    CMD_GET_GROUP_GAINOFFSET   ,
    CMD_SET_GROUP_GAINOFFSET   ,
    CMD_GET_SIZINGCURVE ,
    CMD_SET_SIZINGCURVE ,

    CMD_MAX_MAX_MAX  ,

    CMD_ENABLE_DATA_TRANSFER ,

    CMD_GET_VAL_GROUP_QTY ,
    CMD_GET_VAL_TOTAL_DATA_SIZE ,
    CMD_GET_VAL_GROUP_DATA_SIZE = 40,
    CMD_GET_VAL_GROUP_DATA_OFFSET ,
    CMD_GET_VAL_GROUP_BEAM_OFFSET ,
    CMD_GET_VAL_GROUP_BEAM_LENGTH ,

    CMD_GET_VAL_GAIN  ,
    CMD_SET_VAL_GAIN  ,

    CMD_GET_VAL_START ,
    CMD_SET_VAL_START ,

    CMD_GET_VAL_RANGE ,
    CMD_SET_VAL_RANGE ,


    CMD_GET_VAL_POINT_QTY = 50,
    CMD_SET_VAL_POINT_QTY ,

    CMD_GET_VAL_WEDGEDELAY ,
    CMD_SET_VAL_WEDGEDELAY ,

    CMD_GET_VAL_VELOCITY   ,
    CMD_SET_VAL_VELOCITY   ,

    CMD_GET_VAL_PRF   ,
    CMD_SET_VAL_PRF   ,

    CMD_GET_EXITPOINTE,
    CMD_GET_ALL_DATA,
    CMD_SET_SCAN_START = 60,
    CMD_GET_INSPECT_CONFIG
} ;

#endif // CMDCONFIG

