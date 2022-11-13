package sample;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class Controller {
    int i =0;
    String str = "";
    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button b1;

    @FXML
    private Button b2;

    @FXML
    private Label lab;

    @FXML
    void initialize() {
       b1.setOnAction(event -> {
           i++;
           lab.setText(str+i);
       });
       b2.setOnAction(event ->{
           i--;
           lab.setText(str+i);
       });

    }
}

