#include "intrinsics_test_data.h"

/*--------------------------------------------------------------------------------*/
/* Input/Output Buffers */
/*--------------------------------------------------------------------------------*/

q63_t intrinsics_output_fut[INTRINSICS_MAX_LEN] = {0};
q63_t intrinsics_output_ref[INTRINSICS_MAX_LEN] = {0};
float32_t intrinsics_output_f32_fut[INTRINSICS_MAX_LEN] = {0};
float32_t intrinsics_output_f32_ref[INTRINSICS_MAX_LEN] = {0};

const q63_t intrinsics_q63_inputs[INTRINSICS_MAX_LEN] =
{
    0xF7D2D6F5414A5524, 0x5297DAF44CAB5A17, 0x54129B222D6F5B56, 0x54141F6F7DAF4E3B, 0x44C414A529B226EB, 0x22D4CAB541F6F6A,
    0x6053A44325CE38BF, 0x33D055403A970AFA, 0x0133D0603A44382A, 0x32513D5605540F8, 0x03A25CE33D060524, 0x03A3A97013D56570,
    0x3402674117D7791D, 0x72140A667FE0438C, 0x439218E426741841, 0x11739FF340A66E54, 0x67F17D77218E4386, 0x4267FE0439FF3726,
    0x46C411420DC177CA, 0x7156C147702F2CF5, 0x26615F6441142FF1, 0x20D662C46C1476AB, 0x7700DC1715F640DD, 0x441702F2662C4E49,
    0x50D4F8B538055E7E, 0x5570D192770871FE, 0x725576474F8B5360, 0x538258550D1928A0, 0x2773805557647821, 0x74F77087258558CF,
    0x05066D230C0C604D, 0x63650FA350A46C19, 0x66C3646266D2370D, 0x30C6CE0050FA359A, 0x3500C0C636462E24, 0x26650A466CE00F5C,
    0x21E3B72166D40948, 0x0731EB61355B5831, 0x577733943B72150A, 0x166773F21EB61530, 0x13566D4073394127, 0x43B355B5773F26F4,
    0x7221CF5118052980, 0x27A22AD1038D6587, 0x67C7A8121CF517F4, 0x1187CDC722AD1691, 0x103180527A812473, 0x21C038D67CDC7D7F,
    0x21A0FD604A5110D0, 0x1201A2156D895BB9, 0x53D20EB60FD60F35, 0x04A3DE621A215530, 0x56D4A51120EB6DDA, 0x60F6D8953DE62516,
    0x02C61E17250123E1, 0x26D2CBB35ED813C8, 0x15B6D35061E175B1, 0x7255B1402CBB32F3, 0x35E250126D350907, 0x0615ED815B140D7E,
    0x126418B76EAE272D, 0x23C26BB13E221841, 0x1243CF01418B7B88, 0x76E24DB126BB1B80, 0x13E6EAE23CF010E4, 0x1413E22124DB166C,
    0x1634700479AB7E42, 0x74163F5662DF28D1, 0x246419E047004665, 0x47946BE163F56FC6, 0x66279AB7419E0C75, 0x04762DF246BE1F38,
    0x63F5CE12243239B2, 0x31F3F574758D03E0, 0x0711F4455CE12926, 0x22471D563F574B74, 0x475243231F4458E2, 0x55C758D071D5639,
    0x34806EF703A17B49, 0x77D48D32173A7C76, 0x70F7D3E306EF7531, 0x7030F2F348D32F34, 0x21703A177D3E3063, 0x306173A70F2F3549,
    0x54426F835C314C9, 0x42E447B118CB6B6D, 0x6502E32326F83697, 0x35C50745447B1E9C, 0x1185C3142E323A33, 0x32618CB650745715,
    0x51D4891001AC5746, 0x5601DA36655A4E04, 0x42060E624891060F, 0x00120BF51DA36B4F, 0x66501AC560E6227F, 0x248655A420BF5EB4,
    0x1154156550B3225B, 0x2181540540C10544, 0x02318586415656C, 0x550236A115405EAE, 0x54050B32185863E1, 0x64140C10236A1C4E,
    0x44E7736608BD21F9, 0x2614EDF52ACF7A68, 0x752617A1773665E5, 0x608524F44EDF5F66, 0x52A08BD2617A1610, 0x1772ACF7524F4968,
    0x06A24DC242D006CD, 0x0376A4F55F000079, 0x01D3706424DC2447, 0x2421DE706A4F5599, 0x55F42D0037064D4A, 0x4245F0001DE70608,
    0x44018061233A2EE5, 0x22440795137E488E, 0x44424A8118061B7B, 0x12344CE44079569D, 0x513233A224A817D5, 0x118137E444CE48F5,
    0x41D71AD7575F7883, 0x73C1D4A522406802, 0x6333CBC771AD70BB, 0x757335841D4A5D79, 0x522575F73CBC7CE4, 0x77122406335840D8,
    0x3333D19605792E47, 0x233331A427AD2C05, 0x213330353D196EAB, 0x60513D93331A40AF, 0x4270579233035831, 0x53D27AD213D93987,
    0x0135DC437C542094, 0x25C13796045F317E, 0x37D5C2015DC43F8B, 0x37C7DD501379650C, 0x6047C5425C20193F, 0x15D045F37DD50298,
    0x5275C8A71D482B82, 0x210272914A6B6062, 0x63510E165C8A757B, 0x71D355A5272917C1, 0x14A1D48210E16FBC, 0x65C4A6B6355A5882,
    0x1757DF7F66F86A35, 0x61A758A6604555A1, 0x5531A1137DF7FBB, 0xF6653541758A6216, 0x66066F861A113463, 0x37D6045553541BAD,
    0x04E1F05221576756, 0x6554EA63483B6D8D, 0x67B55B841F052FCC, 0x2217B2E04EA63DFB, 0x3482157655B84677, 0x41F483B67B2E04F2,
    0x41D46029787A796C, 0x71A1DB2204A12CD3, 0x2061A8C746029BD, 0x978061E41DB22DD8, 0x204787A71A8C7F28, 0x74604A12061E452E,
    0x66B73357132D3F78, 0x3626BBB076525852, 0x53F6253673357BBA, 0x7133F6B66BBB0A58, 0x076132D362536AFA, 0x673765253F6B65EF,
    0x55F66B026DC57B58, 0x7325FF601EB718CE, 0x17F3247766B02740, 0x26D7FF355FF60B47, 0x01E6DC5732477B8F, 0x7661EB717FF35302,
    0x7206FF9529FD3E40, 0x34720182475A43D1, 0x44C47E076FF9528A, 0x5294CF572018209D, 0x24729FD347E079C9, 0x76F475A44CF576D3,
    0x2512340428074E34, 0x42551CE35D6F58ED, 0x56425297234045D1, 0x4286443251CE35F9, 0x35D2807425297896, 0x7235D6F5644320FE,
    0x04E701D50F4449A9, 0x4714E09454C361C6, 0x661718F0701D52F1, 0x50F615404E094820, 0x4540F444718F0810, 0x07054C3661540689,
    0x46A48AC379DE5A1F, 0x5216A0C152865C23, 0x57021B7048AC3A4B, 0x379708646A0C1BE0, 0x15279DE521B705DB, 0x048528657086465D,
    0x7206D2311CC10929, 0x038204951E1D716E, 0x71438FF16D231D4C, 0x11C149C720495108, 0x51E1CC1038FF1971, 0x16D1E1D7149C78D4,
    0x62169C32441F1E8B, 0x147210B743D95372, 0x5024781569C324B4, 0x24402476210B7DC9, 0x743441F147815E78, 0x56943D9502476137,
    0x30E2F6846163DDF, 0xD020E680390D6EC2, 0x612022322F684E5B, 0x461125930E680ABD, 0x0396163D02232615, 0x22F390D612593380,
    0x76D130F57B1465FE, 0x6106D772065A6957, 0x66310E91130F53EB, 0x57B63BC76D772EF7, 0x2067B14610E916B6, 0x113065A663BC7A68,
    0x773194712ACB00BB, 0x05973090651C5590, 0x53459BB6194714B5, 0x12A34867730904EE, 0x0652ACB059BB61B4, 0x619651C534867DBC,
    0x21228931391C706C, 0x713129A63C164218, 0x4621317128931CD0, 0x13962882129A66AB, 0x63C391C713171F4D, 0x1283C16462882872,
    0x6547A7944B167FD4, 0x73054B1566902F4C, 0x239308567A794932, 0x44B3946654B152C, 0x5664B16730856EA9, 0x67A6690239466D55,
    0x651077A336696451, 0x63651B950F5B1E8C, 0x11D367E2077A3C6A, 0x3361D2C651B956B4, 0x50F36696367E2D2A, 0x2070F5B11D2C662A,
    0x24D4070678FB6880, 0x6204DF964E6D40B6, 0x4632030640706FDC, 0x678638124DF9679C, 0x64E78FB620306EDB, 0x6404E6D463812AE7,
    0x2043E036255D2748, 0x25504E441B8B617B, 0x66655A373E036FAD, 0x625669B204E444A7, 0x41B255D255A37517, 0x73E1B8B6669B2988,
    0x27634BB318FD5E8C, 0x5057699467BD05CE, 0x06D05B9534BB346C, 0x3186DFA276994800, 0x46718FD505B958B6, 0x53467BD06DFA2FEF,
    0x573727212055B5C, 0xB5F73EF61F843C4C, 0x3435FB9072721B52, 0x1204323573EF6B86, 0x61F2055B5FB90B61, 0x0721F84343235DAC,
    0x17B162F231D424B4, 0x2797B2A7768C0D7E, 0x04479392162F2F9D, 0x231442D17B2A7A99, 0x77631D4279392693, 0x216768C0442D12C0,
    0x1445D9560692273E, 0x20D44E7359A16E80, 0x65F0D8745D956856, 0x6065F5C144E73DAC, 0x359069220D874532, 0x45D59A165F5C1DD0,
    0x3591D8215D167858, 0x7595965405597EA2, 0x71A594C01D821476, 0x15D1A87359654ED2, 0x4055D167594C0DC7, 0x01D055971A873506,
    0xD1F20CC33F693200, 0x3781F9E67A651AB5, 0x12A78E7620CC3C8A, 0x33F2A01D1F9E662C, 0x67A3F69378E7631, 0x6207A6512A01DA0,
    0x073360D43088472F, 0x40D7333712EE0D42, 0x0230D634360D4D5F, 0x430233A073337E48, 0x712308840D634C06, 0x43612EE0233A0ACB,
    0x13E26223706651ED, 0x5223EBB67AA54079, 0x432225A4262239D1, 0x370325813EBB6BB6, 0x67A70665225A4F3D, 0x4267AA5432581A06,
    0x51075ED16E6F5780, 0x53C10DF2577377C7, 0x7373C79275ED1DDC, 0x16E3717510DF2D15, 0x2576E6F53C7929BC, 0x2755773737175917,
    0x47376435354E381C, 0x35273BB7762A2DD7, 0x26C52FE476435AC1, 0x5356C81473BB749E, 0x776354E352FE4E7E, 0x476762A26C8140F4,
    0x1374742257694875, 0x4123792612D30822, 0x020121C7474227CF, 0x257204E137926D98, 0x61257694121C7E24, 0x74712D30204E1EE7,
    0x77A316C358C6268, 0x2617AB142152080, 0x07D61C13316C3323, 0x3587D8E77AB14A31, 0x42158C6261C13C03, 0x331215207D8E74F1,
    0x5673BFD773F446D0, 0x43E672426C6C6A0A, 0x60F3E5523BFD79FB, 0x7730FF5567242969, 0x26C73F443E5524EB, 0x23B6C6C60FF5534,
    0x779540F452F05F1C, 0x5417984617102DE3, 0x21941954540F4A21, 0x452193F7798468E7, 0x61752F05419545EB, 0x45417102193F7880,
    0x5404BF662B246B20, 0x64C40894408A2BC4, 0x2244CAA64BF66A49, 0x62B2478540894C55, 0x4402B2464CAA6398, 0x64B408A2247856E9,
    0x55070D372F2A647D, 0x6595063422F55D33, 0x52B5983670D37915, 0x72F2BCC550634C72, 0x4222F2A65983671, 0x67022F552BCC5AF8,
    0x03A710741A77D48, 0xD613A6B3411B5CFA, 0x5626142571074D7E, 0x41A627103A6B3593, 0x3411A77D61425F05, 0x571411B56271012A,
    0x32310A505B830310, 0x021239F73D8418CA, 0x17F213D510A50792, 0x05B7F993239F7137, 0x73D5B830213D5071, 0x5103D8417F9930D4,
    0x265291502462664F, 0x6146586354180F8E, 0x018144B2291505BA, 0x02418E426586387A, 0x35424626144B2C12, 0x2295418018E425C7,
    0x558194623AA43373, 0x37258B4518F0503C, 0x5267247319462AC0, 0x23A26BF558B452EF, 0x5183AA4372473895, 0x31918F0526BF5435,
    0x13D5C3376DA553B, 0x54D3D93C60912FA6, 0x2204D0355C337331, 0x76D206913D93CD7, 0xC606DA554D035752, 0x55C6091220691929,
    0x25F758B6389962F9, 0x6595FCA636E701E9, 0x02D59602758B642C, 0x6382D5A25FCA69E3, 0x63638996596027F4, 0x27536E702D5A2FD0,
    0x01B76BA35F18324A, 0x33C1BC213DB165AA, 0x6733CC1076BA3876, 0x35F73A601BC21AF6, 0x13D5F1833CC10841, 0x0763DB1673A60174,
    0x66144586625B7F58, 0x72B6157367C57724, 0x7032B3704458653C, 0x66203DF661573095, 0x367625B72B370837, 0x04467C5703DF6CE3,
    0x260191B45D086EFA, 0x630608433F5227C2, 0x21030DE1191B4785, 0x45D105E260843D82, 0x33F5D08630DE11F1, 0x1193F522105E226C,
    0x23B366766E1C7AA2, 0x7733B8D447AA5D14, 0x5407372636676D03, 0x66E409523B8D4DF6, 0x4476E1C77372694, 0x63647AA5409521DC,
    0x5632BE46744206A, 0x04A63E114722023F, 0x05C4A4A02BE46AD5, 0x6745CF2563E11D76, 0x147744204A4A09AB, 0x02B472205CF252B9,
    0x62D3203731586916, 0x6452D7324DFD7D84, 0x72E4524532037634, 0x7312E5362D7329D4, 0x24D315864524582F, 0x5324DFD72E5366C1,
    0x50A6A2543B0E019B, 0x0110A6A038530C6A, 0x054119726A2542D, 0x43B540650A6A00E5, 0x0383B0E0119725CC, 0x26A3853054065347,
    0x571181111B6F7AF1, 0x774716746CCF71F1, 0x77774F43181117F2, 0x11B77A5571674A76, 0x46C1B6F774F43880, 0x3186CCF777A55F47,
    0x0243CBB259EA5B62, 0x547245C44A331D95, 0x1074718D3CBB276F, 0x25907CE0245C4D50, 0x44A59EA54718D5, 0xD3C4A33107CE05D1,
    0x6663006160D47AD5, 0x73D669B325CA1C40, 0x1193D5F130061766, 0x16019306669B39DF, 0x32560D473D5F1320, 0x13025CA119306AD3,
    0x12D6A6E628B30325, 0x02B2DF160DD090F, 0x9312B5146A6E6F37, 0x628311012DF16F66, 0x60D28B302B514C7E, 0x46A0DD0931101C58,
    0x14177AB07D4847FC, 0x43A41320515341CA, 0x4243AF8577AB0EA6, 0x07D24B3141320DAF, 0x0517D4843AF8531E, 0x5775153424B31611,
    0x072222516D377331, 0x73B722D17A832A22, 0x2263B194222511C7, 0x16D261B0722D1F89, 0x17A6D3773B194F18, 0x4227A832261B0A4D,
    0x620190F243F676DB, 0x756202E74F8C6D61, 0x630560D4190F2250, 0x243308E6202E72A9, 0x74F43F67560D4EA2, 0x4194F8C6308E67B4,
    0x17F27EB236746663, 0x6267FDE017CC3852, 0x3232647127EB2EAC, 0x236232617FDE0AA8, 0x01736746264719A, 0x12717CC323261EDD,
    0x42448D823C0B339E, 0x34324D4406284D40, 0x44B4363148D82ECB, 0x23C4BF0424D44CF8, 0x4063C0B343631B91, 0x148062844BF04248,
    0x320630B736497B9B, 0x76C20CC368273C58, 0x3576C3B7630B7AF9, 0x7365744320CC3F26, 0x368364976C3B7B71, 0x76368273574433ED,
    0x626565B07A2552F6, 0x56726F924CDE642D, 0x65B67A20565B0142, 0x07A5B50626F9207F, 0x24C7A25567A207BE, 0x0564CDE65B506684,
    0x1411561044DA4780, 0x46E4155611756A0C, 0x61D6E3A6156104AF, 0x0441DBA1415561B0, 0x61144DA46E3A6886, 0x615117561DBA1EA2,
    0x71D758F0542359C8, 0x52D1DD634C024E22, 0x4612D194758F052A, 0x054616471DD6395, 0x34C542352D194BAD, 0x4754C024616475A1,
    0x35713CB542084602, 0x46057FE209C274AD, 0x716607A413CB5562, 0x5421672357FE2D5B, 0x20942084607A4EE5, 0x41309C2716723A91,
    0x73D28FE64F624CCF, 0x4323DDA62E5E24A3, 0x21932AF528FE6FAF, 0x64F19A573DDA6EF4, 0x62E4F62432AF540C, 0x5282E5E219A57B3B,
    0x353278445D1D73A3, 0x7425397123424B3E, 0x452427D7278445F5, 0x45D5221353971C3B, 0x1235D1D7427D7943, 0x727234245221358C,
    0x7603B86626CE1A5E, 0x145608317B506CA4, 0x62145E143B86636E, 0x62621B7760831F6D, 0x17B26CE145E142F3, 0x43B7B50621B77B04,
    0x43B7D8D17BB65E0C, 0x52D3BF3378B80F5E, 0x02B2D5727D8D172B, 0x17B2B5B43BF33A90, 0x3787BB652D572D9, 0x27D78B802B5B4920,
    0x11C47C6436A05E01, 0x5301CAA652745306, 0x54D304A247C64855, 0x4364D6B11CAA669B, 0x65236A05304A2641, 0x247527454D6B1760,
    0x54B24A673E176D79, 0x64E4BDE7523241B0, 0x44C4E5F124A67957, 0x73E4C2154BDE76AF, 0x7523E1764E5F1493, 0x124523244C215DA5,
    0x53940AE633A052B, 0x569390D11A4D00C2, 0x05A69E8640AE6BCA, 0x6335AF35390D106B, 0x11A33A0569E86018, 0x6401A4D05AF356CF,
    0x10D14B6263561D4, 0x14C0D2E244F31C6, 0x1454CBF114B6299B, 0x26345AC10D2E25F0, 0x244635614CBF132A, 0x11444F3145AC18B6,
    0x222263442227567D, 0x52422C5106B54E2F, 0x46C2442326344534, 0x4226C37222C515EC, 0x106222752442370D, 0x32606B546C3721C6,
    0x6606AF3634EF687D, 0x66A603961C06323A, 0x3496AE706AF36A60, 0x63449D0660396F52, 0x61C34EF66AE70AA1, 0x06A1C06349D06CBC,
    0x1663A9A26F9576C8, 0x71D66DF0584C4258, 0x4571D4803A9A27BB, 0x26F57DD166DF0D47, 0x0586F9571D4804EA, 0x03A584C457DD1E67,
    0x66225C12789C7895, 0x74F6274275336111, 0x63F4FBF625C122C8, 0x2783F9F662742114, 0x275789C74FBF6D26, 0x625753363F9F6482,
    0x77E499E266F02CD9, 0x2447EBC111083202, 0x34944011499E2618, 0x26649DF77EBC1351, 0x11166F02440112F1, 0x1491108349DF7BC1,
    0x16B61AF13BF45C25, 0x52D6B1F731BA7FA0, 0x7632D86561AF1AED, 0x13B63E016B1F7D29, 0x7313BF452D865294, 0x56131BA763E01129,
    0x2081FE3A7E9E77A5, 0x77208597100435D7, 0x331722841FE3A71, 0xA7E31C5208597C81, 0x7107E9E7722849FA, 0x41F1004331C520AF,
    0x1155CA077BA178DC, 0x702150E67F102D31, 0x25D02C345CA07864, 0x77B5D041150E6F98, 0x67F7BA1702C34882, 0x45C7F1025D041F11,
    0x355426F30C613C57, 0x37A5599253984FD1, 0x42B7AFA0426F38AD, 0x30C2B25355992B1D, 0x2530C6137AFA078D, 0x042539842B253413,
    0x51A28933594B32CF, 0x3291A0B432887E38, 0x765291B428933B46, 0x359653A51A0B4168, 0x432594B3291B4A94, 0x42832887653A5E8D,
    0x65030DA421746BBE, 0x63450C565EFE6415, 0x6523471130DA429C, 0x421529C650C5640C, 0x65E2174634711AA4, 0x1305EFE6529C67A6,
    0x42803CA0105957CD, 0x525283854D287499, 0x74225A0403CA0AA7, 0x010420D428385832, 0x54D1059525A04A02, 0x4034D287420D47A4,
    0x72759E2135627556, 0x74527E834BC11E4C, 0x1224586159E215C7, 0x1352282727E838B4, 0x34B35627458612F4, 0x1594BC1122827F6F,
    0x64F4E495449D4DBA, 0x4394FD27679B7362, 0x737395E74E495845, 0x544375A64FD270D1, 0x767449D4395E76A0, 0x74E679B7375A655E,
    0x05161EF712E2058F, 0x06751FF573F970CA, 0x77F6741061EF73B3, 0x7127FDA051FF5362, 0x57312E2067410345, 0x06173F977FDA0B3B,
    0x14B26557221962E8, 0x6264B30017AB6543, 0x67E268E126557412, 0x7227E0D14B30084D, 0x01722196268E191D, 0x12617AB67E0D13DF,
    0x65677FA773EF127D, 0x112560024DEC5DB1, 0x51512DD077FA745F, 0x773157F656002898, 0x24D73EF112DD0A40, 0x0774DEC5157F6DDF,
    0x3337B63042A55F8E, 0x532338B643597924, 0x74F329457B630C3F, 0x0424FA23338B6B58, 0x64342A5532945F75, 0x57B435974FA23A0E,
    0x02406114036E38C0, 0x3192466033B18FD, 0x81219BB006114337, 0x403124C024660ACB, 0x033036E319BB02F0, 0x00633B18124C0A47,
    0x5360C6123A951701, 0x1513607401155ABF, 0x563516600C612D71, 0x23A635F536074CA7, 0x4013A95151660C41, 0x00C01155635F58C7,
    0x50165B077FC2002D, 0x079015F60E6A7CF3, 0x76E791B765B07D07, 0x77F6E475015F6A6B, 0x60E7FC20791B70DD, 0x7650E6A76E475719,
    0x74671942424314C7, 0x167464A268426EB, 0x66B6775771942FEE, 0x2426BA77464A2F52, 0x26842431677579FD, 0x771684266BA775AE,
    0x31D78D951F66EFF, 0xE3B1D0B31A795237, 0x52F3BD3478D9545F, 0x51F2F8531D0B344D, 0x31A1F66E3BD34AB7, 0x4781A7952F85312A,
    0x20208DF316C542AD, 0x46D028113990185D, 0x1406D35108DF3351, 0x3164066202811AA5, 0x13916C546D351F41, 0x108399014066269D,
    0x1355DD7006B660BF, 0x66835D746EDB4768, 0x411689E25DD70CF0, 0x0061143135D74F6E, 0x46E06B66689E220C, 0x25D6EDB411431687,
    0x01D302F0147C49C9, 0x4481DAB6385762BD, 0x63748325302F0AE4, 0x01437D501DAB67F8, 0x638147C4483256C9, 0x5303857637D50FCB,
    0x15819DB74EA82711, 0x26A58DE04D7B2C98, 0x2376AFF719DB78BC, 0x74E3762158DE0DC2, 0x04D4EA826AFF7E7B, 0x7194D7B237621C93,
    0x32E7F884792C6E19, 0x66C2E19677001192, 0x16A6C7137F88439D, 0x4796AF432E196A66, 0x677792C66C71378C, 0x37F770016AF43B3A,
    0x06D4BEE17C16225E, 0x2346D5B56687337, 0x368345D44BEE1608, 0x17C681206D5B5552, 0x5667C162345D4590, 0x44B66873681209CC,
    0x11F198807B242819, 0x2241FC72508A1416, 0x16A24BD019880FE3, 0x07B6A1D11FC7288A, 0x2507B24224BD0502, 0x019508A16A1D1678,
    0x45E5ADE120E6CA0, 0xC7A5EA8659BE2057, 0x2117A2005ADE11EB, 0x120114945EA8649D, 0x65920E6C7A200E6F, 0x05A59BE21149481D,
    0x5636731272281E93, 0x15263B840A5B0451, 0x07C5221767312D58, 0x2727CDF563B849F1, 0x40A7228152217960, 0x7670A5B07CDF59F3,
    0x5347DF1533C775C0, 0x73834E961EBA0799, 0x05E38FC77DF1506, 0x5335EA0534E96110, 0x61E33C7738FC73E3, 0x77D1EBA05EA059B2,
    0x16C43911022936EA, 0x31C6C0D1316406F6, 0x0381C6F343911185, 0x10238DB16C0D10F3, 0x131022931C6F3DF8, 0x3433164038DB12A9,
    0x5775F4A35CD41244, 0x14C77CE12C9F0A7B, 0x0314C8005F4A315F, 0x35C318D577CE1C66, 0x12C5CD414C800860, 0x05F2C9F0318D53E0,
    0x421750817105420D, 0x420217E4575361F2, 0x64D20101750810BA, 0x1714D884217E4CA5, 0x457710542010140, 0x175575364D884763,
    0x008141C642BB0DA7, 0x046087F532D53A74, 0x32D464B5141C6CD4, 0x6422D2A0087F5FC3, 0x53242BB0464B53, 0x51432D532D2A05F6,
    0x5223EB9215532B45, 0x21F221465D5C3CE1, 0x3111FC523EB9216A, 0x21511AE52214611B, 0x65D155321FC52C5F, 0x23E5D5C311AE5DD7,
    0x46D7400020B925A9, 0x2386D0E07C640AF4, 0x00938E6A740009AC, 0x020091046D0E0321, 0x07C20B9238E6A61, 0xA747C64009104544,
    0x666341A6474F26C8, 0x2596619015254CF3, 0x424598B2341A6B59, 0x64724126661904CE, 0x015474F2598B2197, 0x234152542412659D,
    0x13008FD161976DD4, 0x63430400329B3E16, 0x3553456308FD1FB0, 0x16155CC1304006F3, 0x032619763456309, 0x308329B355CC15F1,
    0x0350036D59DA7630, 0x729353775C801335, 0x175299470036D52, 0xD5975280353775A5, 0x75C59DA7299476EB, 0x7005C80175280568,
    0x37F64761766F5264, 0x51B7FB302EA233A6, 0x3361BC03647619F3, 0x17636BC37FB30C7A, 0x02E766F51BC03B9, 0x3642EA2336BC3061,
    0x7640AC043F30596E, 0x51E641973E2A527B, 0x5211ECC30AC04220, 0x43F21447641979A3, 0x73E3F3051ECC3B89, 0x30A3E2A521447BC1,
    0x157299E54E8F2E26, 0x21D57C940C5A1D90, 0x1761D486299E5467, 0x54E76F3157C947E3, 0x40C4E8F21D4865ED, 0x6290C5A176F31C3D,
    0x05C6FFB34EE81CDF, 0x1305C8233479195E, 0x147300F76FFB3AE1, 0x34E479405C82398, 0x3344EE81300F7364, 0x76F3479147940AFA,
    0xF3A224A33B853E3E, 0x3223A674598C440D, 0x42E22880224A3D89, 0x33B2E77F3A674204, 0x4593B85322880A38, 0x022598C42E77F2D,
    0x6091FE9022841C9C, 0x12D093354F0609C3, 0x07E2D6B61FE90922, 0x0227EDB609335017, 0x54F228412D6B69A7, 0x61F4F0607EDB63F9,
    0xE2524BE1099A74EF, 0x716251D21F9F1B40, 0x12816AC524BE17E8, 0x10928D7E251D2F7A, 0x21F099A716AC50D3, 0x5241F9F128D7ED6,
    0x36430DF66D193443, 0x36364FF676156F1B, 0x67463DB230DF6A4E, 0x66D7435364FF6794, 0x6766D19363DB2C9A, 0x2307615674353022,
    0x16742501556E025C, 0x070675A123802AF9, 0x27F70B22425018A4, 0x1557FB01675A18BB, 0x123556E070B227B9, 0x242238027FB01BF,
    0x14F6574563E7910, 0x9524F6E36C661591, 0x11E52B3265745D2B, 0x5631E6A14F6E379D, 0x36C63E7952B32FAC, 0x2656C6611E6A1101,
    0x34B469701DE22385, 0x2544BAB42338191F, 0x17854EB4469704B6, 0x01D783934BAB4599, 0x4231DE2254EB4809, 0x4462338178393E6D,
    0x02D288D5550017DD, 0x1202D52639B120E1, 0x24E20D22288D52D3, 0x5554E1202D52668C, 0x6395500120D22A68, 0x22839B124E1207D1,
    0x734251773FCC0EFE, 0x05A34BF547F37E64, 0x76F5A8D325177A90, 0x73F6F72734BF5D4D, 0x5473FCC05A8D3DCE, 0x32547F376F7275A8,
    0x70A64DB56BEA2655, 0x22C0A4D42A1810FC, 0x1712C40264DB593A, 0x56B71C070A4D4BC0, 0x42A6BEA22C402E93, 0x2642A18171C077F9,
    0x458752F16F0C4577, 0x42C582E370412414, 0x24D2C455752F1DC1, 0x16F4DCD4582E38EA, 0x3706F0C42C455F7B, 0x575704124DCD4EDB,
    0x53D4FCA112BC2696, 0x2503D5E77B037135, 0x736502F44FCA1F8C, 0x112361653D5E75F6, 0x77B12BC2502F41B0, 0x44F7B037361653F1,
    0x64657E702E5B0E31, 0x047467B320266B19, 0x61F4703257E703D7, 0x02E1F776467B3E00, 0x3202E5B047032BA3, 0x257202661F776B9C,
    0x07D1BD5062570A84, 0x07F7D0A27EC75B48, 0x5297FCC21BD5012, 0x062291307D0A2D5D, 0x27E625707FCC29F2, 0x21B7EC75291304B6,
    0xE3A7D12719D558ED, 0x55F3ADE047551C8, 0x1255F7417D12738F, 0x71925D2E3ADE0892, 0x04719D555F741997, 0x17D4755125D2E2F,
    0x65415E922B9F2269, 0x227544375C134FED, 0x456272D315E92399, 0x22B5618654437F4E, 0x75C2B9F2272D32AB, 0x3155C13456186AA1,
    0x8462A8717E4D355C, 0x32C4637A234D7836, 0x75F2C1832A871760, 0x17E5FC784637A94, 0xA237E4D32C183207, 0x32A234D75FC78B3,
    0x34E6C9F47F10621E, 0x6624E3F1276966B2, 0x62562BA26C9F4A11, 0x47F25F234E3F182C, 0x1277F10662BA2EF5, 0x26C2769625F239CD,
    0x63F0AC1573D63FED, 0x3733F3D3636E1F5E, 0x135738320AC15A0E, 0x57335C363F3D33EB, 0x36373D63738326EA, 0x20A636E135C366B1,
    0x642711A14D476E86, 0x67E426A402F63208, 0x3757E4D1711A1FC1, 0x14D75E46426A4396, 0x4024D4767E4D1B93, 0x17102F6375E46DB7,
    0x60A7AD242F3C44A7, 0x4490A56351A56F5C, 0x64C499527AD2463D, 0x42F4C4B60A5639CA, 0x3512F3C449952C78, 0x27A51A564C4B64F6,
    0x14B438673AFE7F8D, 0x7554BC1466993D04, 0x36855A8743867F37, 0x73A681A14BC146C2, 0x4663AFE755A875EC, 0x74366993681A1A75,
    0x61820F7730A67E1B, 0x773189184A4A7D0C, 0x7547389720F77993, 0x730542661891805, 0x84A30A67738976AD, 0x7204A4A7542667D6,
    0x6442BF173C5C6EBF, 0x668447C34499187F, 0x17A68D842BF17C97, 0x73C7AAB6447C317F, 0x3443C5C668D8419C, 0x42B449917AAB6456,
    0x43D09163421B4F29, 0x41A3D72A76740F9C, 0x0751AD5409163B8D, 0x342754943D72AAB, 0xA76421B41AD54DD7, 0x40976740754946EE,
    0x654105637317342B, 0x30C54BB4218546D4, 0x45D0CE6310563DA7, 0x3735D14654BB4CCE, 0x421731730CE63E46, 0x310218545D146234,
    0x40709D7233BE6C63, 0x63607C36325044E5, 0x42D3655309D72335, 0x2332DFA407C36BA, 0x63233BE6365530CC, 0x309325042DFA448C,
    0x312150271663516F, 0x53C1253259B00AA, 0x0493CEF0150274EA, 0x716492F312532D4A, 0x259166353CEF002D, 0x01559B00492F3DA5,
    0x72F14A10263A2574, 0x2682F6276F8005C2, 0x0266829314A10651, 0x026269872F627ABA, 0x76F263A268293238, 0x3146F80026987646,
    0x12B59B1552590516, 0x0532B2A410144D36, 0x4275395359B151B9, 0x552278512B2A4F05, 0x4105259053953699, 0x3591014427851C75,
    0xF4F32843180646F3, 0x54718F4F2E970306, 0x6623953632843145, 0x318D315E18F4FE8F
};

/* The source data is random across the q63_t range. Accessing it by word should
   remain random. */
const q31_t *intrinsics_q31_inputs = ( q31_t * ) intrinsics_q63_inputs;
