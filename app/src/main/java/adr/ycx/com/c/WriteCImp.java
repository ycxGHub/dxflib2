package adr.ycx.com.c;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.nio.charset.Charset;
import java.util.ArrayList;

/**
 * 创建日期：2017/9/21
 * 创建者ycx
 */

public class WriteCImp {
    public WriteC mWriteC;
    public String filePath;
    public DXFVersion mDXFVersion;
    public boolean isInite = false;
    public ArrayList<CoordPoint> pointData = new ArrayList<>();
    public ArrayList<CoordPoint> lineData = new ArrayList<>();
    public ArrayList<CoordPoint> circleData = new ArrayList<>();

    public enum DXFVersion {
        AC1009, AC1015
    }

    public void init(DXFVersion version, String filePath) throws IOException {
        mWriteC = new WriteC();
        int i = 0;
        switch (version) {
            case AC1009:
                i = 1;
                break;
            case AC1015:
                i = 4;
                break;
            default:
                i = 1;
                break;
        }
        File file = new File(filePath);
        if (!file.exists()) {
            file.createNewFile();
        }
        this.filePath=filePath;
        mWriteC.init(i, filePath);
        mWriteC.startEnity();
        isInite = true;
    }

    public void addText(double x, double y, double z, String text) {
        if (text == null) {
            text = "";
        }
        pointData.add(new CoordPoint(x, y, z, text));
    }

    public void addLine(double x1, double y1, double z1, double x2, double y2, double z2) {
        CoordPoint coordPoint = new CoordPoint(x1, y1, z1, x2, y2, z2);
        lineData.add(coordPoint);
    }

    public void addCircle(double x1, double y1, double radius) {
        CoordPoint coordPoint = new CoordPoint();
        coordPoint.x1 = x1;
        coordPoint.y1 = y1;
        coordPoint.z1 = radius;
        circleData.add(coordPoint);
    }

    public void end() throws IOException {
        for (CoordPoint coordPoint : pointData) {
            mWriteC.addText(coordPoint.x1, coordPoint.y1, coordPoint.z1, coordPoint.name1);
        }
        for (CoordPoint coordPoint : lineData) {
            mWriteC.addLine(coordPoint.x1, coordPoint.y1, coordPoint.z1, coordPoint.x2, coordPoint.y2, coordPoint.z2);
        }
        for (CoordPoint coordPoint : circleData) {
            mWriteC.addCircle(coordPoint.z1, coordPoint.x1, coordPoint.y1, 0);
        }
        mWriteC.endEnity();
        mWriteC.close();
        convertFile();
    }

    public void convertFile() throws IOException {
        File file=new File(filePath);
        convert(file);
    }

    private void convert(File file) throws IOException {
        // 如果是文件则进行编码转换，写入覆盖原文件
        int fileCount = 0;
        Charset sourceCharset = Charset.forName("utf-8");
        Charset targetCharset = Charset.forName("gbk");
        if (file.isFile()) {
            InputStreamReader isr = new InputStreamReader(new FileInputStream(
                    file), sourceCharset);
            BufferedReader br = new BufferedReader(isr);
            StringBuffer sb = new StringBuffer();
            String line = null;
            while ((line = br.readLine()) != null) {
                // 注意写入换行符
                sb.append(line + "\n");
            }
            br.close();
            isr.close();

            OutputStreamWriter osw = new OutputStreamWriter(
                    new FileOutputStream(file), targetCharset);
            BufferedWriter bw = new BufferedWriter(osw);
            // 以字符串的形式一次性写入
            bw.write(sb.toString());
            bw.close();
            osw.close();

            System.out.println("Deal:" + file.getPath());

        }
    }
}



