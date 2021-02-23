extends PanelContainer


onready var join_secret_line_edit: = $VBoxContainer/MarginContainer/JoinSecret/LineEdit


func _ready() -> void:
	var _err = DiscordManager.activities.connect(
		"activity_join",
		self, "_on_activity_join"
	)


func _on_activity_join(join_secret: String) -> void:
	join_secret_line_edit.text = join_secret
