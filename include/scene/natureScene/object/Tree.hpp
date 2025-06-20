#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <random>
#include <memory>
#include "scene/natureScene/mesh/Tree.hpp"
#include "objects/Object.hpp"
#include "utilities/Input.hpp"

class Tree : public Object
{
public:
  Tree() : Object()
  {

std::vector<glm::vec3> positions = {
    { -17.2684f, -7.3808f, 173.0373f },
    { -18.1008f, -0.5465f, -16.1361f },
    { 48.6580f, -9.6761f, 191.2987f },
    { -133.5076f, -9.4012f, 126.9631f },
    { 205.2419f, -7.0504f, -16.0283f },
    { 70.5486f, -9.5703f, 199.2768f },
    { 154.1660f, -7.5495f, 191.5855f },
    { -65.6159f, -7.2242f, 149.0690f },
    { 57.1003f, -2.4411f, -3.8579f },
    { 102.2695f, -6.7570f, 193.8548f },
    { 234.5774f, -7.4430f, 112.6759f },
    { -117.1154f, -10.7179f, 155.5344f },
    { -145.3143f, -9.0694f, 106.5398f },
    { 200.5195f, -5.1967f, -61.9796f },
    { -19.0391f, -7.8403f, 186.6651f },
    { -58.7211f, -6.0001f, 170.1319f },
    { 29.5210f, -9.3858f, 202.1378f },
    { 235.9454f, -6.0353f, 47.5502f },
    { 30.3145f, -9.1366f, 190.7323f },
    { 229.7113f, -7.2073f, 32.5811f },
    { -2.0479f, 0.6773f, -9.2117f },
    { 70.1474f, -8.9879f, 207.9068f },
    { 11.8101f, -8.6709f, 183.9161f },
    { 198.8485f, -10.2289f, 131.9214f },
    { -94.3649f, -9.1379f, 154.9461f },
    { -91.9025f, -8.6281f, 146.7661f },
    { 231.8470f, -6.4105f, 7.4130f },
    { -96.3442f, -9.4578f, 160.0340f },
    { 200.0061f, -10.2780f, 153.5260f },
    { 15.5944f, -8.5024f, 182.5461f },
    { 27.3685f, -8.6746f, 193.7523f },
    { 239.6331f, -5.2954f, 92.3834f },
    { -7.5265f, 0.6860f, -14.7099f },
    { 106.7357f, -6.2081f, 203.4710f },
    { -21.2418f, -0.8374f, -31.1518f },
    { 197.4957f, -10.3903f, 152.9077f },
    { 205.8906f, -7.3495f, -11.6657f },
    { 201.1278f, -5.7722f, -40.6235f },
    { 233.7644f, -6.8546f, 110.1467f },
    { 241.4110f, -6.5336f, 31.4688f },
    { -97.9679f, 1.0097f, -54.7152f },
    { 214.3313f, -6.9739f, -22.1635f },
    { -37.9060f, -3.5024f, -13.7779f },
    { 230.0074f, -6.3868f, 64.3474f },
    { 217.7150f, -6.5377f, -20.0707f },
    { 51.8155f, -4.1428f, -17.8919f },
    { 202.4403f, -5.6277f, -45.6570f },
    { 129.5168f, -6.6856f, 2.1041f },
    { 12.3296f, 1.6597f, -25.6715f },
    { 86.0515f, -5.5537f, 18.4987f },
    { 55.9769f, -4.4364f, -14.6615f },
    { 205.6668f, -10.3649f, 146.4857f },
    { 229.7260f, -6.0045f, 90.8978f },
    { 54.7340f, -9.1583f, 199.6060f },
    { -106.6775f, 0.8191f, -33.6994f },
    { -118.7954f, -7.5378f, -81.4606f },
    { 89.8972f, -7.4637f, 203.7123f },
    { 113.0660f, -7.4397f, 189.6116f },
    { 44.3486f, -8.6518f, 191.3096f },
    { 108.6410f, -5.4906f, 8.6791f },
    { 221.1807f, -7.5847f, 8.0532f },
    { 66.2799f, -5.0968f, 15.8739f },
    { 236.7863f, -6.1865f, 103.3957f },
    { 6.6805f, -8.6822f, 179.8934f },
    { 102.3998f, -5.9788f, 211.3600f },
    { 186.7869f, -10.7041f, 138.9293f },
    { -163.3941f, -9.4921f, 85.4480f },
    { 19.2661f, -0.1627f, -7.5782f },
    { -97.9031f, -8.1889f, 134.3548f },
    { 178.0717f, -5.3099f, -33.4382f },
    { -119.5035f, -7.6728f, -92.9883f },
    { -53.1518f, 3.4821f, -62.0881f },
    { 88.8743f, -7.3854f, 199.1284f },
    { 154.0800f, -6.5625f, -12.4616f },
    { 197.2860f, -9.1839f, -1.8710f },
    { -134.5597f, -9.4080f, 108.9831f },
    { 200.3053f, -10.0318f, 139.3577f },
    { 120.9485f, -6.6905f, 203.7603f },
    { 179.6114f, -5.2118f, -36.4169f },
    { 132.3175f, -8.6506f, 162.6764f },
    { 105.1129f, -5.7218f, 12.7871f },
    { 222.8506f, -7.0283f, 50.7639f },
    { 198.4345f, -4.9137f, -54.1776f },
    { 177.1680f, 0.2469f, -75.1379f },
    { -70.4332f, -7.5294f, 160.9360f },
    { 56.7911f, -8.7279f, 199.7763f },
    { 215.3189f, -9.3447f, 143.7520f },
    { 195.3648f, -10.3909f, 149.9357f },
    { -5.3726f, -8.3989f, 184.4401f },
    { 28.0064f, -9.0725f, 188.1589f },
    { 219.8373f, -8.3828f, 15.8786f },
    { 190.6610f, -3.6322f, -55.2197f },
    { 200.9799f, -5.9411f, -37.7383f },
    { 77.7894f, -8.3789f, 215.5000f },
    { 166.4247f, -8.2623f, -8.2426f },
    { -78.3674f, 0.3662f, -41.3352f },
    { -100.1988f, 1.6529f, -44.4769f },
    { 24.6643f, -9.2599f, 188.5344f },
    { 193.4276f, -4.3212f, -52.3585f },
    { 175.3401f, -5.1929f, -33.5774f },
    { 177.3367f, -11.5606f, -16.4240f },
    { 72.4028f, -5.4150f, 19.9192f },
    { -59.4061f, -6.2747f, 174.0417f },
    { 199.8086f, -10.4703f, 134.1305f },
    { -84.5241f, -2.8603f, -25.9974f },
    { -50.7508f, -6.5736f, 167.5184f },
    { 152.7484f, 1.6504f, -100.7614f },
    { 192.2974f, -2.9181f, -62.7999f },
    { -108.2184f, -8.9473f, 137.9427f },
    { -53.2250f, -0.4779f, -38.3615f },
    { 197.3105f, -4.2739f, -60.4261f },
    { 189.5486f, -10.4078f, 157.1352f },
    { 122.9793f, -6.9956f, 192.0783f },
    { -120.6583f, -7.1495f, -76.5657f },
    { 228.5368f, -6.4991f, 86.1358f },
    { 48.9070f, -8.6163f, 201.3907f },
    { -52.5743f, 2.7534f, -69.2022f },
    { 82.3972f, -8.3798f, 202.8960f },
    { 230.7674f, -5.8456f, 93.3260f },
    { -103.6450f, -9.3144f, 149.6576f },
    { 69.9221f, -8.6316f, 206.4128f },
    { 1.0076f, -8.1465f, 187.9810f },
    { 217.7740f, -8.3612f, 106.9842f },
    { 176.2224f, 0.3804f, -75.2842f },
    { 222.2370f, -6.9880f, 52.1952f },
    { 69.8877f, -4.9763f, 18.0028f },
    { -70.9117f, -7.4826f, 149.3823f },
    { 70.6155f, -8.5224f, 199.9075f },
    { -53.1619f, -6.4588f, 173.9111f },
    { 0.4256f, 0.3279f, -5.8264f },
    { -97.7365f, 1.9501f, -43.0682f },
    { -74.6091f, -6.8071f, 165.1864f },
    { -87.2048f, 2.5554f, -46.1528f },
    { 17.0094f, 2.7053f, -23.6955f },
    { -3.3614f, -7.5895f, 178.9076f },
    { 106.5178f, -4.5162f, 3.0012f },
    { 47.0638f, -1.9455f, -5.5251f },
    { 185.2260f, -10.1120f, 145.0867f },
    { 237.5212f, -6.3361f, 101.6353f },
    { 9.7861f, 1.0534f, -29.8020f },
    { 224.1796f, -7.8876f, 15.0853f },
    { 145.7891f, -8.6800f, 174.9828f },
    { 93.9806f, -7.6347f, 209.2748f },
    { -162.1234f, -9.5343f, 85.3435f },
    { 102.4160f, -7.6778f, 175.2043f },
    { -155.8396f, -9.7665f, 84.3487f },
    { 9.3133f, -7.9010f, 183.6446f },
    { 7.4532f, 0.8595f, -30.2292f },
    { 145.5453f, -7.0015f, 199.8849f },
    { 179.9443f, -5.1411f, -41.1440f },
    { 173.1409f, -6.8937f, -15.9589f },
    { -11.1835f, -8.1828f, 183.5430f },
    { 146.9296f, -7.8717f, 182.9660f },
    { -101.6993f, -2.0226f, -26.4658f },
    { -125.2762f, -9.7278f, -23.1869f },
    { -123.8709f, -10.3995f, -5.5433f },
    { -104.6659f, -9.0947f, -9.1345f },
    { -114.8149f, -2.8603f, -30.0570f },
    { -110.2869f, -6.9455f, -18.1905f },
    { -53.2165f, -3.2595f, -10.8689f },
    { -44.7958f, -3.6972f, 1.5326f }
};

std::vector<glm::vec3> rotations = {
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 89.9999f, -0.0001f, 0.0000f },
    { 90.0002f, 0.0002f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0198f, -0.0007f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 89.8610f, 0.1377f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 89.9999f, 0.0198f, 0.0000f },
    { 90.0001f, 0.0001f, 0.0000f },
    { 90.0001f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 89.9999f, -0.0001f, 0.0000f },
    { 90.0211f, -0.0075f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0001f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0001f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0001f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0001f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0198f, 0.0000f },
    { 90.0001f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0410f, -0.0359f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0003f, 0.0001f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 89.9998f, 0.0001f, 0.0000f },
    { 90.0000f, -0.0198f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 89.9999f, -0.0001f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0001f, 0.0000f },
    { 89.9999f, 0.0001f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 89.9213f, -0.0762f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0001f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0001f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0003f, 0.0001f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0732f, -0.0705f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0001f, 0.0279f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 89.3309f, 0.6690f, 0.0000f },
    { 90.0008f, 0.0194f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0198f, 0.0000f },
    { 90.0004f, -0.0004f, 0.0000f },
    { 90.0000f, -0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, -75.7211f, 0.0000f },
    { 90.0000f, -75.7211f, 0.0000f },
    { 90.0000f, -75.7211f, 0.0000f },
    { 90.0000f, -75.7211f, 0.0000f },
    { 90.0000f, -75.7211f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f },
    { 90.0000f, 0.0000f, 0.0000f }
};

std::vector<glm::vec3> scales = {
    { 0.6203f, 0.6203f, 0.6203f },
    { 0.5602f, 0.5602f, 0.5602f },
    { 0.7081f, 0.7081f, 0.7081f },
    { 0.5042f, 0.5042f, 0.5042f },
    { 0.9553f, 0.9553f, 0.9553f },
    { 0.8841f, 0.8841f, 0.8841f },
    { 0.2491f, 0.2491f, 0.2491f },
    { 0.3938f, 0.3938f, 0.3938f },
    { 0.5315f, 0.5315f, 0.5315f },
    { 0.0272f, 0.0272f, 0.0272f },
    { 0.9842f, 0.9842f, 0.9842f },
    { 0.8842f, 0.8842f, 0.8842f },
    { 0.5128f, 0.5128f, 0.5128f },
    { 0.8841f, 0.8841f, 0.8841f },
    { 0.9714f, 0.9714f, 0.9714f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.6209f, 0.6209f, 0.6209f },
    { 0.1577f, 0.1577f, 0.1577f },
    { 0.5768f, 0.5768f, 0.5768f },
    { 0.4093f, 0.4093f, 0.4093f },
    { 0.1996f, 0.1996f, 0.1996f },
    { 0.4480f, 0.4480f, 0.4480f },
    { 0.6896f, 0.6896f, 0.6896f },
    { 0.6047f, 0.6047f, 0.6047f },
    { 0.9552f, 0.9552f, 0.9552f },
    { 0.6896f, 0.6896f, 0.6896f },
    { 0.0403f, 0.0403f, 0.0403f },
    { 0.8221f, 0.8221f, 0.8221f },
    { 0.6896f, 0.6896f, 0.6896f },
    { 0.3938f, 0.3938f, 0.3938f },
    { 0.0714f, 0.0714f, 0.0714f },
    { 0.0615f, 0.0615f, 0.0615f },
    { 0.5315f, 0.5315f, 0.5315f },
    { 0.1997f, 0.1997f, 0.1997f },
    { 0.5301f, 0.5301f, 0.5301f },
    { 0.7082f, 0.7082f, 0.7082f },
    { 0.7212f, 0.7212f, 0.7212f },
    { 0.4927f, 0.4927f, 0.4927f },
    { 0.5596f, 0.5596f, 0.5596f },
    { 0.2490f, 0.2490f, 0.2490f },
    { 0.8142f, 0.8142f, 0.8142f },
    { 0.9144f, 0.9144f, 0.9144f },
    { 0.6203f, 0.6203f, 0.6203f },
    { 0.7606f, 0.7606f, 0.7606f },
    { 0.3124f, 0.3124f, 0.3124f },
    { 0.1996f, 0.1996f, 0.1996f },
    { 0.2785f, 0.2785f, 0.2785f },
    { 0.1651f, 0.1651f, 0.1651f },
    { 0.3937f, 0.3937f, 0.3937f },
    { 0.4062f, 0.4062f, 0.4062f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.9552f, 0.9552f, 0.9552f },
    { 0.1995f, 0.1995f, 0.1995f },
    { 0.5750f, 0.5750f, 0.5750f },
    { 0.0715f, 0.0715f, 0.0715f },
    { 0.5314f, 0.5314f, 0.5314f },
    { 0.4061f, 0.4061f, 0.4061f },
    { 0.7271f, 0.7271f, 0.7271f },
    { 0.0295f, 0.0295f, 0.0295f },
    { 0.5751f, 0.5751f, 0.5751f },
    { 0.2462f, 0.2462f, 0.2462f },
    { 0.5602f, 0.5602f, 0.5602f },
    { 0.2682f, 0.2682f, 0.2682f },
    { 0.9842f, 0.9842f, 0.9842f },
    { 0.0507f, 0.0507f, 0.0507f },
    { 0.5766f, 0.5766f, 0.5766f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.6203f, 0.6203f, 0.6203f },
    { 0.6210f, 0.6210f, 0.6210f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.5602f, 0.5602f, 0.5602f },
    { 0.8842f, 0.8842f, 0.8842f },
    { 0.0837f, 0.0837f, 0.0837f },
    { 0.0615f, 0.0615f, 0.0615f },
    { 0.8221f, 0.8221f, 0.8221f },
    { 0.8142f, 0.8142f, 0.8142f },
    { 0.4384f, 0.4384f, 0.4384f },
    { 0.9341f, 0.9341f, 0.9341f },
    { 0.1996f, 0.1996f, 0.1996f },
    { 0.5315f, 0.5315f, 0.5315f },
    { 0.0273f, 0.0273f, 0.0273f },
    { 0.5602f, 0.5602f, 0.5602f },
    { 0.5301f, 0.5301f, 0.5301f },
    { 0.5601f, 0.5601f, 0.5601f },
    { 0.9842f, 0.9842f, 0.9842f },
    { 0.1652f, 0.1652f, 0.1652f },
    { 0.3937f, 0.3937f, 0.3937f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.9553f, 0.9553f, 0.9553f },
    { 0.5301f, 0.5301f, 0.5301f },
    { 0.6203f, 0.6203f, 0.6203f },
    { 0.4622f, 0.4622f, 0.4622f },
    { 0.6895f, 0.6895f, 0.6895f },
    { 0.1179f, 0.1179f, 0.1179f },
    { 0.2682f, 0.2682f, 0.2682f },
    { 0.6209f, 0.6209f, 0.6209f },
    { 0.8174f, 0.8174f, 0.8174f },
    { 0.7800f, 0.7800f, 0.7800f },
    { 0.5043f, 0.5043f, 0.5043f },
    { 0.3938f, 0.3938f, 0.3938f },
    { 0.9841f, 0.9841f, 0.9841f },
    { 0.0872f, 0.0872f, 0.0872f },
    { 0.1997f, 0.1997f, 0.1997f },
    { 0.8841f, 0.8841f, 0.8841f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.5603f, 0.5603f, 0.5603f },
    { 0.2462f, 0.2462f, 0.2462f },
    { 0.6209f, 0.6209f, 0.6209f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.0726f, 0.0726f, 0.0726f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.6209f, 0.6209f, 0.6209f },
    { 0.5603f, 0.5603f, 0.5603f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.7272f, 0.7272f, 0.7272f },
    { 0.0726f, 0.0726f, 0.0726f },
    { 0.7082f, 0.7082f, 0.7082f },
    { 0.6557f, 0.6557f, 0.6557f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.7082f, 0.7082f, 0.7082f },
    { 0.0872f, 0.0872f, 0.0872f },
    { 0.2491f, 0.2491f, 0.2491f },
    { 0.8220f, 0.8220f, 0.8220f },
    { 0.5314f, 0.5314f, 0.5314f },
    { 0.5315f, 0.5315f, 0.5315f },
    { 0.0084f, 0.0084f, 0.0084f },
    { 0.5009f, 0.5009f, 0.5009f },
    { 0.1934f, 0.1934f, 0.1934f },
    { 0.5316f, 0.5316f, 0.5316f },
    { 0.0506f, 0.0506f, 0.0506f },
    { 0.5043f, 0.5043f, 0.5043f },
    { 0.2682f, 0.2682f, 0.2682f },
    { 0.2490f, 0.2490f, 0.2490f },
    { 0.0154f, 0.0154f, 0.0154f },
    { 0.2682f, 0.2682f, 0.2682f },
    { 0.1934f, 0.1934f, 0.1934f },
    { 0.7884f, 0.7884f, 0.7884f },
    { 0.0714f, 0.0714f, 0.0714f },
    { 0.5805f, 0.5805f, 0.5805f },
    { 0.5010f, 0.5010f, 0.5010f },
    { 0.5128f, 0.5128f, 0.5128f },
    { 0.6203f, 0.6203f, 0.6203f },
    { 0.5004f, 0.5004f, 0.5004f },
    { 0.1995f, 0.1995f, 0.1995f },
    { 0.0084f, 0.0084f, 0.0084f },
    { 0.5601f, 0.5601f, 0.5601f },
    { 0.0315f, 0.0315f, 0.0315f },
    { 0.0315f, 0.0315f, 0.0315f },
    { 0.5127f, 0.5127f, 0.5127f },
    { 0.7272f, 0.7272f, 0.7272f },
    { 0.0315f, 0.0315f, 0.0315f },
    { 0.8221f, 0.8221f, 0.8221f },
    { 0.4092f, 0.4092f, 0.4092f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 0.6182f, 0.6182f, 0.6182f },
    { 1.0296f, 1.0296f, 1.0296f },
    { 0.6203f, 0.6203f, 0.6203f }
};

    auto meshes = std::vector<std::shared_ptr<Mesh>>();
    meshes.reserve(positions.size() * 2);

    for (int i = 0; i < positions.size(); ++i)
    {
      {
        auto wood = std::make_shared<TreeWoodMesh>();
        auto leaves = std::make_shared<TreeLeavesMesh>();

        auto pos = positions[i];
        auto rot = rotations[i];
        rot.x -= 90.0f; // Adjust rotation to match the tree's orientation
        auto scale = scales[i];

        wood->transform.setPosition(pos);
        leaves->transform.setPosition(pos);

        wood->transform.setRotation(rot);
        leaves->transform.setRotation(rot);

        wood->transform.setScale(scale);
        leaves->transform.setScale(scale);

        meshes.push_back(wood);
        meshes.push_back(leaves);
      }

      this->setMeshes(meshes);
    }
  }
};

#endif // TREE_HPP