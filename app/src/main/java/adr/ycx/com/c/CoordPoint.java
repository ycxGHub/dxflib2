package adr.ycx.com.c;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

/**
 * 创建日期：2017/9/21
 * 创建者ycx
 */
@Getter
@Setter
@NoArgsConstructor
public class CoordPoint {
    public double x1 = 0;//centerX
    public double y1 = 0;//centery
    public double z1 = 0;//radius
    public double x2 = 0;
    public double y2 = 0;
    public double z2 = 0;
    public String name1 = "";
    public String name2 = "";

    public CoordPoint(double x1, double y1, double z1, String name1) {
        this.x1 = x1;
        this.y1 = y1;
        this.z1 = z1;
        this.name1 = name1;
    }

    public CoordPoint(double x1, double y1, double z1, double x2, double y2, double z2) {
        this.x1 = x1;
        this.y1 = y1;
        this.z1 = z1;
        this.x2 = x2;
        this.y2 = y2;
        this.z2 = z2;
    }
}
