package adr.ycx.com.c;

/**
 * 创建日期：2017/9/19
 * 创建者ycx
 */

public class WriteC {

    static {
        System.loadLibrary("native-lib");
    }
    public native void startEnity();
    public native void addPoint(double x,double y,double z);
    public native void addText(double x,double y,double z,String text);
    public native void addLine(double x1,double y1,double z1,double x2,double y2,double z3);
    public native void addCircle(double radius,double x1,double y1,double y2);
    public native void endEnity();
    public native int init(int verison,String filepath);
    public native void close();
}
