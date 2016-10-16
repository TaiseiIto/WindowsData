import javax.swing.JFrame;
//import javax.swing.ImageIcon;
import java.awt.Dimension;
import java.awt.GraphicsEnvironment;

class HelloJFrame
{
	public static void main(String args[])
	{
		JFrame jFrame = new JFrame("Hello,JFrame!");
		Dimension screenSize = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDefaultConfiguration().getBounds().getSize();
		//ImageIcon icon = new ImageIcon("./Taisei Ito.png");
		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		jFrame.setBounds(0, 0, (int)screenSize.getWidth(), (int)screenSize.getHeight());
		//jFrame.setIconImage(icon.getImage());
		jFrame.setVisible(true);
		return;
	}
}
