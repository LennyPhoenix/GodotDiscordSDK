extends PanelContainer


onready var size_options: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/Size/OptionButton
onready var id_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/InputFields/VBoxContainer/ID
onready var result_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Result/LineEdit
onready var width_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Dimensions/Width/LineEdit
onready var height_line_edit: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/Dimensions/Height/LineEdit
onready var image_texture_rect: = $VBoxContainer/MarginContainer/VBoxContainer/OutputFields/VBoxContainer/FetchedImage/VBoxContainer/TextureRect


func _ready() -> void:
	for i in range(5):
		var value: = pow(2, i + 4)
		size_options.add_item(str(value), value)


func _on_fetch_button_down() -> void:
	var id: String = id_line_edit.text
	var size: int = size_options.get_selected_id()

	var handle: = Discord.ImageHandle.new()
	handle.id = int(id)
	handle.size = size
#	handle.type = Discord.ImageType.USER

	DiscordManager.images.fetch(handle, true)
	var ret: Array = yield(DiscordManager.images, "fetch_callback")
	var result: int = ret[0]
	handle = ret[1]

	result_line_edit.text = DiscordManager.enum_to_string(
		Discord.Result,
		result
	)

	if result == Discord.Result.OK:
		DiscordManager.images.get_dimensions(handle)
		ret = yield(DiscordManager.images, "get_dimensions_callback")
		result = ret[0]
		var dimensions: Discord.ImageDimensions = ret[1]

		if result == Discord.Result.OK:
			width_line_edit.text = str(dimensions.width)
			height_line_edit.text = str(dimensions.height)

		DiscordManager.images.get_data(handle)
		ret = yield(DiscordManager.images, "get_data_callback")
		result = ret[0]
		var data: PoolByteArray = ret[1]

		if result == Discord.Result.OK:
			var image: = Image.new()
			image.create_from_data(
				dimensions.width, dimensions.height,
				false, Image.FORMAT_RGBA8,
				data
			)
			image.unlock()

			var texture: = ImageTexture.new()
			texture.create_from_image(image, Texture.FLAG_MIPMAPS)

			image_texture_rect.texture = texture
