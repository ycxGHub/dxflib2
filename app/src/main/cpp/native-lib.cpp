#include <jni.h>
#include <string>
#include "dl_writer_ascii.h"
#include "dl_dxf.h"
#include "Android/log.h"
#include "dl_codes.h"

#define TAG    "myhello-jni-test" //
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)

#define LC_NAME_zh_CN_GBK        LC_NAME_zh_CN "." CSET_GBK
#define LC_NAME_zh_CN_UTF8        LC_NAME_zh_CN "." CSET_UTF8
#define LC_NAME_zh_CN_DEFAULT    LC_NAME_zh_CN_GBK
 DL_Codes::version sversion;
 DL_Attributes attributes = DL_Attributes("mainlayer", 256, -1, "BYLAYER");
DL_Dxf *dxf;
DL_WriterA *dw;

JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_addPoint(JNIEnv *env, jobject instance, jdouble x, jdouble y, jdouble z) {
    DL_PointData data = DL_PointData(x, y, z);
    dxf->writePoint(*dw, data, attributes);
    // TODO

}

extern "C"
JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_addText(JNIEnv *env, jobject instance, jdouble x, jdouble y, jdouble z,
                                  jstring text_) {
    const char *chars = env->GetStringUTFChars(text_, 0);
//    char *chars = NULL;
//    jbyte *bytes;
//    bytes = env->GetByteArrayElements(text_, 0);
//    int chars_len = env->GetArrayLength(text_);
//    chars = new char[chars_len + 1];
//    memset(chars, 0, chars_len + 1);
//    memcpy(chars, bytes, chars_len);
//    chars[chars_len] = 0;
//    env->ReleaseByteArrayElements(text_, bytes, 0);

    // TODO
    DL_TextData data = DL_TextData(x, y, 0, 0, 1, 1, 0, 0, 0, 0, 0, chars, "", 0);
    dxf->writeText(*dw, data, attributes);
    env->ReleaseStringUTFChars(text_, chars);
}
extern "C"
JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_addLine(JNIEnv *env, jobject instance, jdouble x1, jdouble y1, jdouble z1,
                                  jdouble x2, jdouble y2, jdouble z3) {
    DL_LineData data=DL_LineData(x1,y1,z1,x2,y2,z3);
    dxf->writeLine(*dw,data,attributes);
    // TODO

}
extern "C"
JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_addCircle(JNIEnv *env, jobject instance, jdouble radius, jdouble x1,
                                    jdouble y1, jdouble y2) {
    DL_CircleData data=DL_CircleData(x1,y1,y2,radius);
    dxf->writeCircle(*dw,data,attributes);
    // TODO

}



extern "C"
JNIEXPORT jint JNICALL
Java_adr_ycx_com_c_WriteC_init(JNIEnv *env, jobject instance, jint verison, jstring filepath_) {
    const char *filepath = env->GetStringUTFChars(filepath_, 0);
    // TODO const char *filepath_ = env->GetStringUTFChars(filepath, 0);
    switch (verison) {
        case 1:
            sversion = DL_Codes::AC1009;
            break;
        case 2:
            sversion = DL_Codes::AC1012;
            break;
        case 3:
            sversion = DL_Codes::AC1014;
            break;
        case 4:
            sversion = DL_Codes::AC1015;
            break;
        default:
            break;
    }
    dxf = new DL_Dxf();
    dw = dxf->out(filepath, sversion);
    if (dw == NULL) {
        return -1;
    } else {
        dxf->writeHeader(*dw);
        // int variable:
        dw->dxfString(9, "$INSUNITS");
        dw->dxfInt(70, 4);
        // real (double, float) variable:
        dw->dxfString(9, "$DIMEXE");
        dw->dxfReal(40, 1.25);
        // string variable:
        dw->dxfString(9, "$TEXTSTYLE");
        dw->dxfString(7, "Standard");
        // vector variable:
        dw->dxfString(9, "$LIMMIN");
        dw->dxfReal(10, 0.0);
        dw->dxfReal(20, 0.0);
        dw->sectionEnd();
        dw->sectionTables();
        dxf->writeVPort(*dw);
        dw->tableLineTypes(25);
        dxf->writeLineType(*dw, DL_LineTypeData("BYBLOCK", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("BYLAYER", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("CONTINUOUS", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("ACAD_ISO02W100", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("ACAD_ISO03W100", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("ACAD_ISO04W100", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("ACAD_ISO05W100", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("BORDER", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("BORDER2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("BORDERX2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("CENTER", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("CENTER2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("CENTERX2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DASHDOT2", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("DASHDOTX2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DASHED", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DASHED2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DASHEDX2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DIVIDE2", 0));
        dxf->writeLineType(*dw,
                           DL_LineTypeData("DIVIDEX2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DOT", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DOT2", 0));
        dxf->writeLineType(*dw, DL_LineTypeData("DOTX2", 0));
        dw->tableEnd();
        int numberOfLayers = 3;
        dw->tableLayers(numberOfLayers);

        dxf->writeLayer(*dw,
                        DL_LayerData("0", 0),
                        DL_Attributes(
                                std::string(""),      // leave empty
                                DL_Codes::black,        // default color
                                100,                  // default width
                                "CONTINUOUS"));       // default line style

        dxf->writeLayer(*dw,
                        DL_LayerData("mainlayer", 0),
                        DL_Attributes(
                                std::string(""),
                                DL_Codes::red,
                                100,
                                "CONTINUOUS"));

        dxf->writeLayer(*dw,
                        DL_LayerData("anotherlayer", 0),
                        DL_Attributes(
                                std::string(""),
                                DL_Codes::black,
                                100,
                                "CONTINUOUS"));

        dw->tableEnd();
        dxf->writeStyle(*dw);
        dxf->writeView(*dw);
        dxf->writeUcs(*dw);

        dw->tableAppid(1);
        dw->tableAppidEntry(0x12);
        dw->dxfString(2, "ACAD");
        dw->dxfInt(70, 0);
        dw->tableEnd();
        dxf->writeDimStyle(*dw,
                           1,
                           1,
                           1,
                           1,
                           1);
        dxf->writeBlockRecord(*dw);
        dxf->writeBlockRecord(*dw, "myblock1");
        dxf->writeBlockRecord(*dw, "myblock2");
        dw->tableEnd();
        dw->sectionEnd();
        dw->sectionBlocks();

        dxf->writeBlock(*dw,
                        DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
        dxf->writeEndBlock(*dw, "*Model_Space");

        dxf->writeBlock(*dw,
                        DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
        dxf->writeEndBlock(*dw, "*Paper_Space");

        dxf->writeBlock(*dw,
                        DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
        dxf->writeEndBlock(*dw, "*Paper_Space0");

        dxf->writeBlock(*dw,
                        DL_BlockData("myblock1", 0, 0.0, 0.0, 0.0));
        // ...
        // write block entities e.g. with dxf->writeLine(), ..
        // ...
        dxf->writeEndBlock(*dw, "myblock1");

        dxf->writeBlock(*dw,
                        DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
        // ...
        // write block entities e.g. with dxf->writeLine(), ..
        // ...
        dxf->writeEndBlock(*dw, "myblock2");
        dw->sectionEnd();
    }
    env->ReleaseStringUTFChars(filepath_, filepath);
    return 1;
}
extern "C"
JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_close(JNIEnv *env, jobject instance) {

    dw->dxfEOF();
    dw->close();
    delete  dw;
    delete dxf;
    // TODO

}
extern "C"
JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_startEnity(JNIEnv *env, jobject instance) {
    dw->sectionEntities();
    // TODO

}
extern "C"
JNIEXPORT void JNICALL
Java_adr_ycx_com_c_WriteC_endEnity(JNIEnv *env, jobject instance) {
    dw->sectionEnd();
    dxf->writeObjects(*dw);
    dxf->writeObjectsEnd(*dw);
    // TODO

}