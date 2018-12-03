package lab04;

import java.util.ArrayList;

import javax.swing.JPanel;

public class Statistic extends JPanel {

	private static final long serialVersionUID = 1L;
	ArrayList<Result> results = new ArrayList<>();
	
	public Statistic() {
		
	}
	void addResult(Result r) {
		results.add(r);
	}
	Result isUserExists(String _nickName) {
		for(Result res : results) {
			if( res.getnickName().equals(_nickName) )
				return res;
		}
		
		return null;
	}

}
