
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.InputMethodEvent;
import java.awt.event.InputMethodListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

import javax.swing.JButton;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;

import com.skype.Chat;
import com.skype.ChatMessage;
import com.skype.ChatMessageListener;
import com.skype.Skype;
import com.skype.SkypeException;
import com.skype.connector.Connector;
import com.skype.connector.ConnectorException;


/**
* This code was edited or generated using CloudGarden's Jigloo
* SWT/Swing GUI Builder, which is free for non-commercial
* use. If Jigloo is being used commercially (ie, by a corporation,
* company or business for any purpose whatever) then you
* should purchase a license for each developer using Jigloo.
* Please visit www.cloudgarden.com for details.
* Use of Jigloo implies acceptance of these licensing terms.
* A COMMERCIAL LICENSE HAS NOT BEEN PURCHASED FOR
* THIS MACHINE, SO JIGLOO OR THIS CODE CANNOT BE USED
* LEGALLY FOR ANY CORPORATE OR COMMERCIAL PURPOSE.
*/
@SuppressWarnings("serial")
public class JWindowChat extends javax.swing.JDialog implements KeyListener, ActionListener {
	private JButton botaoSend;
	private JTextArea areaDeTexto;
	private JTextArea textAreaUserInput;
	private JScrollPane scrollPaneUserInput;
	private JScrollPane scrollPane;
	private JButton botaoSalvarConversa;
	
	private String idDoContato = "";
	
	private String textoEnviando = "";
	
	private Chat chat = null;
	
	private Connector conn = Connector.getInstance();

	public static void criaJanela(final String idDoContato) throws SkypeException {
		//SwingUtilities.invokeLater(new Runnable() {
		//	public void run() {
				JWindowChat inst = new JWindowChat(idDoContato);
				inst.setVisible(true);
			//}
		//});
	}
	
	public JWindowChat(String idDoContato) throws SkypeException {
		initGUI();
		this.idDoContato = idDoContato;
		this.setTitle("conversatition with: " + idDoContato);
		this.adicionaListener();
	}

	private void initGUI() {
		try {
			{
				getContentPane().setLayout(null);
			}
			{
				botaoSend = new JButton();
				getContentPane().add(botaoSend);
				botaoSend.setText("Send...");
				botaoSend.setBounds(450, 333, 80, 28);
				botaoSend.addKeyListener(this);
				botaoSend.addActionListener(this);
			}
			{
				scrollPane = new JScrollPane();
				getContentPane().add(scrollPane);
				scrollPane.setBounds(6, 6, 524, 286);
				scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);

				{
					areaDeTexto = new JTextArea();
					scrollPane.setViewportView(areaDeTexto);

					/* Wraps the text and the end of the text area. */
					areaDeTexto.setLineWrap(true);		
					areaDeTexto.setEditable(false);
				}
			}
			{
				scrollPaneUserInput = new JScrollPane();
				getContentPane().add(scrollPaneUserInput);
				scrollPaneUserInput.setBounds(6, 298, 438, 63);
				{
					textAreaUserInput = new JTextArea();
					scrollPaneUserInput.setViewportView(textAreaUserInput);
					scrollPaneUserInput.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
					textAreaUserInput.setLineWrap(true);
					textAreaUserInput.addKeyListener(this);
					textAreaUserInput.setFocusable(true);

					textAreaUserInput.grabFocus();
					textAreaUserInput.requestFocus();
					textAreaUserInput.setEnabled(true);
				}
			}
			{
				botaoSalvarConversa = new JButton();
				getContentPane().add(botaoSalvarConversa);
				botaoSalvarConversa.setText("Save Log");
				botaoSalvarConversa.setBounds(450, 298, 80, 28);
				botaoSalvarConversa.addActionListener(this);
			}
			this.setSize(552, 406);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(arg0.getSource() == botaoSend) {

			if(areaDeTexto.getText().equals("")) {
				areaDeTexto.setText(textAreaUserInput.getText());
			} else {
				areaDeTexto.append("\n" + textAreaUserInput.getText());
			}
			textoEnviando = textAreaUserInput.getText();
			textAreaUserInput.setText("");
			
			try {

				if(idDoContato != null && !idDoContato.equals("")) {
					sendMessage(idDoContato, textoEnviando);
				}
				//getMessages();
				
			} catch (Exception e) {
				
				e.printStackTrace();
			}
		}
		
		if(arg0.getSource() == botaoSalvarConversa) {
			//	Salva o conteudo da textArea num arquivo no caminho do projeto
			//com o nome do contato e a hora. O nome do arquivo sera o ID do contato.
			//Se o arquivo jah existir faz append 
			//do conteudo atual no arquivo, caso contrario cria um novo arquivo.
			
			//Para ter as vantagens dos writers, faco um wrap de todos eles juntos.
			
			try {
				
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("" + idDoContato + ".txt", true)));
				Date d = new Date();
				SimpleDateFormat sdf = new SimpleDateFormat("dd/MM/yyyy");
				String data = sdf.format(d);
				pw.println("Conversation History - " + data + " - " + idDoContato);
				pw.println(areaDeTexto.getText());
				pw.flush();
				pw.close();
				
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
	}

	@Override
	public void keyPressed(KeyEvent e) {
		// TODO Auto-generated method stub

	}

	@Override
	public void keyReleased(KeyEvent e) {

		if(e.getKeyCode() == KeyEvent.VK_ENTER) {
			System.out.println(areaDeTexto.getText());
		}
	}

	@Override
	public void keyTyped(KeyEvent e) {
		// TODO Auto-generated method stub
	}
	
	public String getTexto() {
		return textAreaUserInput.getText() != null ? textAreaUserInput.getText() : "";
	}
	
	/* The methods below are used to connect
	 * to skype communication layer. */
	static {
		//Connector.useJNIConnector(true);
	}
	
	public void sendMessage(String id, String text) throws SkypeException {
		chat = (null == chat ? Skype.chat(id) : chat);
		chat.send(text);
	}
	
	public void getMessages() throws SkypeException {
		ChatMessage[] listaDeMensagens = chat.getRecentChatMessages();
		for(int i = 0; i < listaDeMensagens.length; i++) {
			//System.out.println("" + listaDeMensagens[i].getContent());
		}
	}
	
	public String getLastMessage() throws SkypeException {
		ChatMessage[] listaDeMensagens = chat.getRecentChatMessages();
		return  listaDeMensagens[listaDeMensagens.length -1].getContent();
	}

	/*public void connect() throws Exception {
		
		Connector.Status status = null;
		//Connector conn = Connector.getInstance();
		
		try {
			status = conn.connect();
		} catch (ConnectorException e1) {
			e1.printStackTrace();
			throw new Exception(e1.getMessage());
		}

		if (status != Connector.Status.ATTACHED)
			throw new Exception(new Exception(
					"Please install Skype from www.skype.com and run it."));

		// Add Skype4Java listeners.
		try {
			
		} catch (SkypeException e) {
			e.printStackTrace();
		}

		System.out.println("Connected, Skype ver. " + Skype.getVersion());
		
	}*/

	private ChatMessageListener chatMessageListener = new ChatMessageListener() {
		
		@Override
		public void chatMessageSent(ChatMessage arg0) throws SkypeException {
		}

		@Override
		public void chatMessageReceived(ChatMessage chatMessage) throws SkypeException {
			//System.out.println(chatMessage.getSenderDisplayName() + "(" + chatMessage.getSenderId() + "): "	+ chatMessage.getContent());
			areaDeTexto.append("\n" + getLastMessage());
		}
	};
	
	public void adicionaListener() throws SkypeException {
		Skype.addChatMessageListener(chatMessageListener);
	}
	
}
