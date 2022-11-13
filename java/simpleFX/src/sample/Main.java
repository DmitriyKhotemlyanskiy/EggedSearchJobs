package sample;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;



public class Main extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) {
        Scene scene = new Scene(createRoot());
        stage.setTitle("Voting Machine");
        stage.setScene(scene);
        stage.show();
    }
    private int i=0;
    private VBox createRoot() {
        VBox root = new VBox(10);
        HBox myHBox = new HBox(15);

        Button b = new Button("Ofra Haza");
        Button c = new Button("Yardena Arazi");
        b.setFont(new Font("Arial", 20));
        b.setMaxWidth(Double.MAX_VALUE);
        b.setMinWidth(100);
        c.setFont(new Font("Arial", 20));
        c.setMaxWidth(Double.MAX_VALUE);
        c.setMinWidth(100);

        String str = "";
        myHBox.getChildren().addAll(b, c);
        myHBox.setPadding(new Insets(10));
        TextField myText = new TextField();
        myText.setText(str+i);
        myText.setPadding(new Insets(15));
        myText.setAlignment(Pos.CENTER);
        myText.setFont(new Font("Arial", 20));
        myText.setBackground(new Background(new BackgroundFill(Color.BLUE,
                new CornerRadii(5), null)));
        class LabelIncrease implements EventHandler<ActionEvent> {

            public void handle(ActionEvent event) {
                i++;
                myText.setText(str+i);
            }
        }
        class LabelDecrease implements EventHandler<ActionEvent> {

            public void handle(ActionEvent event) {
                i--;
                myText.setText(str+i);
            }
        }
        b.setOnAction( new LabelIncrease());
        c.setOnAction( new LabelDecrease());
        root.getChildren().addAll(myHBox,myText);
        root.setPadding(new Insets(10));
        return root;
    }

}