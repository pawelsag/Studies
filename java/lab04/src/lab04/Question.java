package lab04;


public class Question {
	
	private int id;
	private String questionTopic;
	private String [] possiblAanswers = new String[4];
	private int correctAnswer;
	private static int uniqueId = 0;
	Question(String _title, String A,String B, String C, String D, int _correctAns ){
		
		questionTopic = _title;
		possiblAanswers[0] = A;
		possiblAanswers[1] = B;
		possiblAanswers[2] = C;
		possiblAanswers[3] = D;
		correctAnswer = _correctAns;
		this.id = Question.uniqueId;
		Question.uniqueId++;
	}
	Question(int _id, String _title, String A,String B, String C, String D, int _correctAns ){
		
		questionTopic = _title;
		possiblAanswers[0] = A;
		possiblAanswers[1] = B;
		possiblAanswers[2] = C;
		possiblAanswers[3] = D;
		correctAnswer = _correctAns;
		this.id = _id;

	}
	String getQName() {
		return this.questionTopic;
	}
	String [] getAnserws() {
		return this.possiblAanswers;
	}
	int getCorrectAns() {
		return this.correctAnswer;
	}
	@Override
	public String toString() {	
		return id+1 + ". " + questionTopic;
	}
	
	static int getuniqueId() {
		return Question.uniqueId;
	}
	
	static void setUniqueId(int UID) {
		uniqueId = UID;
	}
	
	int getId() {
		return this.id;
	}
	
	String toDatabaseFormat() {
		String fmt = "";
		fmt += this.id + "," 
		+ this.questionTopic + ","
		+ possiblAanswers[0] + ","
		+ possiblAanswers[1] + ","
		+ possiblAanswers[2] + ","
		+ possiblAanswers[3] + ","
		+ correctAnswer;
		return fmt;
	}
	
	
}
