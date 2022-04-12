class AvatarUploader < CarrierWave::Uploader::Base
  # Include RMagick or MiniMagick support:
  # include CarrierWave::RMagick
  include CarrierWave::MiniMagick

  # Choose what kind of storage to use for this uploader:
  storage :file
  # storage :fog

  # Override the directory where uploaded files will be stored.
  # This is a sensible default for uploaders that are meant to be mounted:
  def store_dir
    "uploads/#{model.class.to_s.underscore}/#{mounted_as}/#{model.id}"
  end

  # Provide a default URL as a default if there hasn't been a file uploaded:
  def default_url(*args)
    ActionController::Base.helpers.asset_path('default_avatar.png')
  end

  version :thumb do
    process resize_to_fit: [50, 80]
  end

  version :medium do
    process resize_to_fit: [300, 400]
  end

  def extension_whitelist
    %w(jpg jpeg gif png)
  end

end
